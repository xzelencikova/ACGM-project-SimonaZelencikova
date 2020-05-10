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
            ShaderInput input = CastShadowRay(min_ray, camera->GetPosition());

            renderer.SetPixel(column, renderer.GetResolution().y - row - 1, CalculateColor(ray, input, index, max_reflection_depth_, max_transparency_depth_, image));

            x += dx;
        }
    }
    //! Free image, when not needed anymore
    if (enviro_image_file_.compare("") != 0)
    {
        image->FreeImage();
    }
}

//! Calculate color for a pixel
cogs::Color3f acgm::Scene::CalculateColor(std::shared_ptr<acgm::Ray> view_ray, ShaderInput input, int index, int max_reflection, int max_transparency, std::shared_ptr<acgm::Image> image) const
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
        //! Calculate color of point
        Color c = models_.at(index)->GetShader()->CalculateColor(input);
        cogs::Color3f transparency_color = cogs::Color3f(0.0f, 0.0f, 0.0f);

        //! If transparent object and transparency didn't reach max hits
        if (c.transparency > 0.0f && max_transparency > 0)
        {
            int internal_reflection = 0;

            //! Calculate refracted direction
            std::optional<glm::vec3> refracted_direction = view_ray->GetRefractionDirection(index_of_refraction_, c.refractive_index, input.normal);
            if (refracted_direction == std::nullopt)
            {
                //! If it's internal reflection, calculate reflected direction
                refracted_direction = view_ray->GetReflectionDirection(input.normal);
                internal_reflection = 1;
            }
            //! Cast refracted ray
            std::shared_ptr<acgm::Ray> refracted_ray = std::make_shared<acgm::Ray>(input.point + *refracted_direction * bias_, *refracted_direction, bias_);

            std::optional<acgm::HitResult> min_ray_t;

            min_ray_t->ray_param = INFINITY;
            int new_index_t = -1;

            //! Find intersection with reflected or refracted ray (based by if it's internal reflection or not)
            for (int i = 0; i < models_.size(); i++)
            {
                std::optional<HitResult> ray_hit = models_.at(i)->Intersect(refracted_ray);

                if (ray_hit->ray_param > 0.0f && ray_hit->ray_param < min_ray_t->ray_param)
                {
                    min_ray_t->ray_param = ray_hit->ray_param;
                    min_ray_t->normal = ray_hit->normal;
                    min_ray_t->point = ray_hit->point;
                    new_index_t = i;
                }
            }

            ShaderInput reflect_input = CastShadowRay(min_ray_t, view_ray->GetOrigin());

            //! If internal reflection, then return reflection 
            if (internal_reflection == 1) 
            {
                transparency_color = c.transparency * CalculateColor(refracted_ray, reflect_input, new_index_t, max_reflection-1, max_transparency, image);
            }
            else
            {
                transparency_color = c.transparency * CalculateColor(refracted_ray, reflect_input, new_index_t, max_reflection, max_transparency - 1, image);
            }
        }

        //! If object without glossiness or with max_reflection reached
        if (c.glossiness > -FLT_EPSILON && c.glossiness < FLT_EPSILON || max_reflection == 0)
        {
            //! If 0 transparency hits allowed, ignore transparency weight in return
            if (max_transparency_depth_ == 0)
                return c.color;
            else return c.color * (1 - c.transparency) + transparency_color;
        }
        else {
            //! Calculate reflected ray
            glm::vec3 reflected_direction = view_ray->GetReflectionDirection(input.normal);
            std::shared_ptr<acgm::Ray> reflected_ray = std::make_shared<acgm::Ray>(input.point + reflected_direction * bias_, reflected_direction, bias_);

            std::optional<acgm::HitResult> min_ray;

            min_ray->ray_param = INFINITY;
            int new_index = -1;

            //! Find intersection with reflected ray
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

            ShaderInput reflect_input = CastShadowRay(min_ray, view_ray->GetOrigin());
            //! Compute reflection color
            return c.color * (1 - c.glossiness - c.transparency) + c.glossiness * CalculateColor(reflected_ray, reflect_input, new_index, max_reflection - 1, max_transparency, image) + transparency_color;
        }      
    }
}

//! Function to find shadows
acgm::ShaderInput acgm::Scene::CastShadowRay(std::optional<acgm::HitResult> hit_point, const glm::vec3 & origin) const
{
    //! Set shader input parameters
    ShaderInput reflect_input;
    reflect_input.is_point_in_shadow = false;
    reflect_input.normal = glm::normalize(hit_point->normal);
    reflect_input.direction_to_light = glm::normalize(light->GetDirectionToLight(hit_point->point));
    reflect_input.point = hit_point->point;
    reflect_input.direction_to_eye = glm::normalize(origin - hit_point->point);
    reflect_input.light_intensity = light->GetIntensityAt(hit_point->point);

    std::shared_ptr <acgm::Ray> shadow_ray = std::make_shared<acgm::Ray>(reflect_input.point + reflect_input.direction_to_light * bias_, reflect_input.direction_to_light, bias_);

    hit_point->ray_param = INFINITY;

    //! Search for nearest intersect shadow ray x model
    for (int i = 0; i < models_.size(); i++)
    {
        std::optional<HitResult> ray_hit = models_.at(i)->Intersect(shadow_ray);

        if (ray_hit->ray_param > 0.0f && ray_hit->ray_param < hit_point->ray_param)
        {
            hit_point->ray_param = ray_hit->ray_param;
        }
    }

    //! Find out, if the point is in shadow
    float get_distance = glm::distance(reflect_input.point, light->GetPosition());

    if (hit_point->ray_param < get_distance)
    {
        reflect_input.is_point_in_shadow = true;
    }

    return reflect_input;
}