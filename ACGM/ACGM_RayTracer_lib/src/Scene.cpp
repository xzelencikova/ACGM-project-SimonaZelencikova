#include <ACGM_RayTracer_lib/Scene.h>
#include <omp.h>

//! Scene constructor
acgm::Scene::Scene(const std::shared_ptr<acgm::Camera>& camera, const std::shared_ptr<acgm::Light>& light, const std::vector<std::shared_ptr<acgm::Model>>& models) : 
    models_(models), camera(camera), light(light)
{
}

//! Scene rendering function
void acgm::Scene::Raytrace(hiro::draw::RasterRenderer &renderer) const
{
    float y;// = tan(camera->GetFovYRad() / 2.0f);
    float x;// = -y;
    
    float dy = 2 * tan(camera->GetFovYRad() / 2.0f) / float(renderer.GetResolution().y);
    float dx = 2 * tan(camera->GetFovYRad() / 2.0f) / float(renderer.GetResolution().x);
    
    std::optional<HitResult> ray_hit;
    std::optional<HitResult> min_ray;

    std::shared_ptr <acgm::Ray> ray;
    std::shared_ptr <acgm::Ray> shadow_ray;

    float bias = 0.001;
    ShaderInput input;

    float test_y = tan(camera->GetFovYRad() / 2.0f);
    float test_x = -test_y;

    int32_t row, column, i, index;
  
    //! OMP works, needs to uncomment, but some pixels are not very well rendered 
//#pragma omp parallel for private(row, column, i, index, ray, shadow_ray, min_ray, ray_hit, input)
    for (row = 0; row < renderer.GetResolution().y; row++)
    {
        for (column = 0; column < renderer.GetResolution().x; column++)
        {
            glm::vec3 direction = glm::normalize(camera->GetForwardDirection() + x * camera->GetRightDirection() + y * camera->GetUpDirection());
            ray = std::make_shared<acgm::Ray>(camera->GetPosition(), direction, bias);

            index = -1;
            min_ray->ray_param = 10000.0f;

            //! Search for nearest intersect ray x model
            for (i = 0; i < models_.size(); i++)
            {
                ray_hit = models_.at(i)->Intersect(ray);
             
                if (ray_hit->ray_param > 0 && ray_hit->ray_param < min_ray->ray_param && ray_hit->ray_param < camera->GetZFar() && ray_hit->ray_param > camera->GetZNear())
                {
                    min_ray->ray_param = ray_hit->ray_param;
                    min_ray->normal = ray_hit->normal;
                    min_ray->point = ray_hit->point;
                    index = i;
                }
            }
            //! Set input params for shader, initializing is_point_in_shadow to false for now
            input.is_point_in_shadow = false;
            input.direction_to_light =  glm::normalize(light->GetDirectionToLight(min_ray->point));
            input.normal = glm::normalize(min_ray->normal);
            input.point = min_ray->point;
            input.direction_to_eye = glm::normalize(camera->GetPosition() - min_ray->point);
            input.light_intensity = light->GetIntensityAt(min_ray->point);
            
            shadow_ray = std::make_shared<acgm::Ray>(input.point, input.direction_to_light, bias);

            min_ray->ray_param = 10000.0f;

            //! Search for nearest intersect shadow ray x model
            for (i = 0; i < models_.size(); i++)
            {
                ray_hit = models_.at(i)->Intersect(shadow_ray);
                
                if (ray_hit->ray_param > 0 && ray_hit->ray_param < min_ray->ray_param)
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

           // x += dx;
            x = ((column + 1) * dx) + test_x;
        }
        //y -= dy;
        y = test_y - ((row + 1) * dy);
        x = -tan(camera->GetFovYRad() / 2.0f);
    }
}
