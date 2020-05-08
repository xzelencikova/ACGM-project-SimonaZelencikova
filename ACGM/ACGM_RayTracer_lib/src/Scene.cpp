#include <ACGM_RayTracer_lib/Scene.h>
#include <omp.h>
#include <glm/gtx/vector_angle.hpp>

#define PI 3.1415927


//! Scene constructor
acgm::Scene::Scene(const std::shared_ptr<acgm::Camera>& camera, const std::shared_ptr<acgm::Light>& light, const std::vector<std::shared_ptr<acgm::Model>>& models,
    const glm::vec3& enviro_up, const glm::vec3& enviro_seam, float bias, std::string enviro_image_file, int max_reflection_depth, int max_transparency_depth,
    const float index_of_refraction) :
    models_(models), camera(camera), light(light), enviro_up_(enviro_up), enviro_seam_(enviro_seam), bias_(bias), enviro_image_file_(enviro_image_file), 
    max_reflection_depth_(max_reflection_depth), max_transparency_depth_(max_transparency_depth), index_of_refraction_(index_of_refraction)
{
}

//! Scene rendering function
void acgm::Scene::Raytrace(hiro::draw::RasterRenderer &renderer) const
{   
    float dy = 2 * tan(camera->GetFovYRad() / 2.0f) / float(renderer.GetResolution().y);
    float dx = 2 * tan(camera->GetFovYRad() / 2.0f) / float(renderer.GetResolution().x);

    float test_y = tan(camera->GetFovYRad() / 2.0f);

    int32_t row, column, i;

    std::shared_ptr<acgm::Image> image = std::make_shared<acgm::Image>(enviro_image_file_);
  
   
    //! OMP to parallelize the rendering
#pragma omp parallel for private(row, column, i)
    for (row = 0; row < renderer.GetResolution().y; row++)
    {
        float y = test_y - (row * dy);
        float x = -tan(camera->GetFovYRad() / 2.0f);
        for (column = 0; column < renderer.GetResolution().x; column++)
        {
            glm::vec3 direction = glm::normalize(camera->GetForwardDirection() + x * camera->GetRightDirection() + y * camera->GetUpDirection());
            std::shared_ptr <acgm::Ray> ray = std::make_shared<acgm::Ray>(camera->GetPosition(), direction, bias_);

            int32_t index = -1;
            std::optional<HitResult> min_ray;
            min_ray->ray_param = INFINITY;

            //! Search for nearest intersect ray x model
            for (i = 0; i < models_.size(); i++)
            {
                std::optional<HitResult> ray_hit = models_.at(i)->Intersect(ray);
             
                if (ray_hit->ray_param > 0.0f && ray_hit->ray_param < min_ray->ray_param && ray_hit->ray_param < camera->GetZFar() && ray_hit->ray_param > camera->GetZNear())
                {
                    min_ray->ray_param = ray_hit->ray_param;
                    min_ray->normal = ray_hit->normal;
                    min_ray->point = ray_hit->point;
                    index = i;
                }
            }

            //! Set input params for shader, initializing is_point_in_shadow to false for now
            ShaderInput input;
            input.is_point_in_shadow = false;
            input.direction_to_light =  glm::normalize(light->GetDirectionToLight(min_ray->point));
            input.normal = glm::normalize(min_ray->normal);
            input.point = min_ray->point;
            input.direction_to_eye = glm::normalize(camera->GetPosition() - min_ray->point);
            input.light_intensity = light->GetIntensityAt(min_ray->point);
            
            std::shared_ptr <acgm::Ray> shadow_ray = std::make_shared<acgm::Ray>(input.point, input.direction_to_light, bias_);

            min_ray->ray_param = INFINITY;

            //! Search for nearest intersect shadow ray x model
            for (i = 0; i < models_.size(); i++)
            {
                std::optional<HitResult> ray_hit = models_.at(i)->Intersect(shadow_ray);
                
                if (ray_hit->ray_param > 0.0f && ray_hit->ray_param < min_ray->ray_param)
                {
                     min_ray->ray_param = ray_hit->ray_param;
                }
            }
            
            //! Find out, if the point is in shadow
            float get_distance = glm::distance(input.point, light->GetPosition());
            
            if (min_ray->ray_param < get_distance)
            {
                input.is_point_in_shadow = true;
            }

            renderer.SetPixel(column, renderer.GetResolution().y - row - 1, ReflectionColor(ray, input, index, max_reflection_depth_, max_transparency_depth_, image));

            x += dx;
        }
    }
}

//! Calculate glossiness color for a pixel
cogs::Color3f acgm::Scene::ReflectionColor(std::shared_ptr<acgm::Ray> view_ray, ShaderInput input, int index, int max_reflection, int max_transparency, std::shared_ptr<acgm::Image> image) const
{
    if (index == -1)
    {
        if (enviro_image_file_.compare("") != 0)
        {
            glm::vec3 orth_vector = view_ray->GetDirection() - enviro_up_ * glm::dot(enviro_up_, view_ray->GetDirection());
            float latitude = std::acos(glm::dot(glm::normalize(enviro_up_), glm::normalize(view_ray->GetDirection())));
            float longitude = glm::orientedAngle(glm::normalize(orth_vector), glm::normalize(enviro_seam_), glm::normalize(enviro_up_));

            //! map long/lat na uv
            //! based on (formula value - down_first_range) * (up_second_range - down_second_range) / (up_first_range - down_first_range)

            //! mapping range <0, PI> to <0, 1>
            float v_coord = latitude / PI;
            //! mapping range <-PI, PI> to <0, 1>
            float u_coord = (longitude + PI) / (2 * PI);
            return image->GetColorAt(glm::vec2(u_coord, v_coord));
        }
        return cogs::Color3f(0.0f, 0.0f, 0.0f);
    }
    else
    {
        Color c = models_.at(index)->GetShader()->CalculateColor(input);
        cogs::Color3f transparency_color = cogs::Color3f(0.0f, 0.0f, 0.0f);

        if (c.transparency > 0.0f && max_transparency > 1)
        {
            float ior;
            if (glm::dot(input.normal, view_ray->GetDirection()) < 0)
            {
                ior = index_of_refraction_ / c.refractive_index;
            }
            else
            {
                ior = c.refractive_index / index_of_refraction_;
            }
            int ref = 0;

            std::optional<glm::vec3> refraction_direction = view_ray->GetRefractionDirection(ior, input.normal);
            if (refraction_direction == std::nullopt)
            {
                refraction_direction = view_ray->GetReflectionDirection(input.normal);
                ref = 1;
            }
            
            std::shared_ptr<acgm::Ray> transparent_ray = std::make_shared<acgm::Ray>(input.point, glm::vec3(refraction_direction->x, refraction_direction->y, refraction_direction->z), view_ray->GetBias());

            std::optional<acgm::HitResult> min_ray_t;

            min_ray_t->ray_param = INFINITY;
            int new_index_t = -1;

            for (int i = 0; i < models_.size(); i++)
            {
                std::optional<HitResult> ray_hit = models_.at(i)->Intersect(transparent_ray);

                if (ray_hit->ray_param > 0.0f && ray_hit->ray_param < min_ray_t->ray_param)
                {
                    min_ray_t->ray_param = ray_hit->ray_param;
                    min_ray_t->normal = ray_hit->normal;
                    min_ray_t->point = ray_hit->point;
                    new_index_t = i;
                }
            }

            ShaderInput reflect_input;
            reflect_input.is_point_in_shadow = false;
            reflect_input.normal = glm::normalize(min_ray_t->normal);
            reflect_input.direction_to_light = glm::normalize(light->GetDirectionToLight(min_ray_t->point));
            reflect_input.point = min_ray_t->point;
            reflect_input.direction_to_eye = glm::normalize(view_ray->GetOrigin() - min_ray_t->point);
            reflect_input.light_intensity = light->GetIntensityAt(min_ray_t->point);

            std::shared_ptr <acgm::Ray> shadow_ray = std::make_shared<acgm::Ray>(reflect_input.point, reflect_input.direction_to_light, bias_);

            min_ray_t->ray_param = INFINITY;

            //! Search for nearest intersect shadow ray x model
            for (int i = 0; i < models_.size(); i++)
            {
                std::optional<HitResult> ray_hit = models_.at(i)->Intersect(shadow_ray);

                if (ray_hit->ray_param > 0.0f && ray_hit->ray_param < min_ray_t->ray_param)
                {
                    min_ray_t->ray_param = ray_hit->ray_param;
                }
            }

            //! Find out, if the point is in shadow
            float get_distance = glm::distance(reflect_input.point, light->GetPosition());

            if (min_ray_t->ray_param < get_distance)
            {
                reflect_input.is_point_in_shadow = true;
            }

            transparency_color += c.transparency * ReflectionColor(transparent_ray, reflect_input, new_index_t, max_reflection, max_transparency - 1, image);
        }

        if (c.glossiness > -FLT_EPSILON && c.glossiness < FLT_EPSILON || max_reflection == 1)
        {
            return c.color * (1 - c.transparency) + transparency_color;
        }
        
        glm::vec3 reflected_direction = view_ray->GetReflectionDirection(input.normal);
        std::shared_ptr<acgm::Ray> reflected_ray = std::make_shared<acgm::Ray>(input.point, reflected_direction, view_ray->GetBias());

        std::optional<acgm::HitResult> min_ray;
            
        min_ray->ray_param = INFINITY;
        int new_index = -1;
            
        for (int i = 0; i < models_.size(); i++)
        {
            std::optional<HitResult> ray_hit = models_.at(i)->Intersect(reflected_ray);

            if (ray_hit->ray_param > 0.0f && ray_hit->ray_param < min_ray->ray_param)
            {
                 min_ray->ray_param = ray_hit->ray_param;
                 min_ray->normal = ray_hit->normal;
                 min_ray->point = ray_hit->point;
                 new_index = i;
            }
        }

        ShaderInput reflect_input;
        reflect_input.is_point_in_shadow = false;
        reflect_input.normal = glm::normalize(min_ray->normal);
        reflect_input.direction_to_light = glm::normalize(light->GetDirectionToLight(min_ray->point));
        reflect_input.point = min_ray->point;
        reflect_input.direction_to_eye = glm::normalize(view_ray->GetOrigin() - min_ray->point);
        reflect_input.light_intensity = light->GetIntensityAt(min_ray->point);

        std::shared_ptr <acgm::Ray> shadow_ray = std::make_shared<acgm::Ray>(reflect_input.point, reflect_input.direction_to_light, bias_);

        min_ray->ray_param = INFINITY;

        //! Search for nearest intersect shadow ray x model
        for (int i = 0; i < models_.size(); i++)
        {
            std::optional<HitResult> ray_hit = models_.at(i)->Intersect(shadow_ray);

            if (ray_hit->ray_param > 0.0f && ray_hit->ray_param < min_ray->ray_param)
            {
                min_ray->ray_param = ray_hit->ray_param;
            }
        }

        //! Find out, if the point is in shadow
        float get_distance = glm::distance(reflect_input.point, light->GetPosition());
            
        if (min_ray->ray_param < get_distance)
        {
            reflect_input.is_point_in_shadow = true;
        }

        return c.color * (1 - c.glossiness - c.transparency) + c.glossiness * ReflectionColor(reflected_ray, reflect_input, new_index, max_reflection - 1, max_transparency, image) + transparency_color;
    }
}