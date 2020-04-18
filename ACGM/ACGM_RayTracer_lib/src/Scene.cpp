#include <ACGM_RayTracer_lib/Scene.h>
#include <omp.h>
#include <glm/gtx/vector_angle.hpp>

#define PI 3.1415927


//! Scene constructor
acgm::Scene::Scene(const std::shared_ptr<acgm::Camera>& camera, const std::shared_ptr<acgm::Light>& light, const std::vector<std::shared_ptr<acgm::Model>>& models,
    const glm::vec3& enviro_up, const glm::vec3& enviro_seam, float bias, std::string enviro_image_file) :
    models_(models), camera(camera), light(light), enviro_up_(enviro_up), enviro_seam_(enviro_seam), bias_(bias), enviro_image_file_(enviro_image_file)
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

            if (index > -1)
            {
                renderer.SetPixel(column, renderer.GetResolution().y - row - 1, models_.at(index)->GetShader()->CalculateColor(input));
            }
            else if (enviro_image_file_.compare("") != 0)
            {
//                float x_y_coord = - enviro_up_.x / enviro_up_.z;
//                float x_z_coord = - enviro_up_.x / enviro_up_.z;
//                printf("%f %f\n", x_y_coord, x_z_coord);

//                glm::vec3 orth_vector = glm::vec3(enviro_up_.x, x_y_coord, x_z_coord);
//                float size_orth_vector = sqrt((orth_vector.x * orth_vector.x) + (orth_vector.y * orth_vector.y) + (orth_vector.z * orth_vector.z));
//                orth_vector = orth_vector / size_orth_vector;

                //! orthonogal vector to enviro_up... since there's only 1 not null value in vec, only 0,0,0 is possible ort vector 
                glm::vec3 orth_vector = glm::cross(glm::normalize(direction), glm::normalize(enviro_up_));
                float latitude = std::acos(glm::dot(glm::normalize(enviro_up_), glm::normalize(direction)));
                float longitude = glm::orientedAngle(glm::normalize(orth_vector), glm::normalize(enviro_seam_), glm::normalize(enviro_up_));

                //! map long/lat na uv
                //! based on (formula value - down_first_range) * (up_second_range - down_second_range) / (up_first_range - down_first_range)
                
                //! mapping range <0, PI> to <0, 1>
                float v_coord = longitude / PI;
                //! mapping range <-PI, PI> to <0, 1>
                float u_coord = (latitude - (-PI)) / (2 * PI);

         //       printf("%f %f %f\n", orth_vector.x, orth_vector.y, orth_vector.z);

                renderer.SetPixel(column, renderer.GetResolution().y - row - 1, image->GetColorAt(glm::vec2(u_coord, v_coord)));
            }

            x += dx;
        }
    }
}
