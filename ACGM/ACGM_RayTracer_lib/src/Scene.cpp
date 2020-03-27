#include <ACGM_RayTracer_lib/Scene.h>
#include <omp.h>


acgm::Scene::Scene(const std::shared_ptr<acgm::Camera>& camera, const std::shared_ptr<acgm::Light>& light, const std::vector<std::shared_ptr<acgm::Model>>& models) : 
    models_(move(models)), camera(camera), light(light)
{
}

void acgm::Scene::Raytrace(hiro::draw::RasterRenderer &renderer) const
{
    int row;
    int column;
    int i;

    float y = tan( camera->GetFovYRad() / 2.0f);
    float x = -y;
    
    float dy = 2 * tan(camera->GetFovYRad() / 2.0f) / float(renderer.GetResolution().y);
    float dx = 2 * tan(camera->GetFovYRad() / 2.0f) / float(renderer.GetResolution().x);
    
    std::shared_ptr <acgm::Ray> shadow_ray;
    std::optional<HitResult> ray_hit;
    std::optional<HitResult> shadow_ray_hit;
    std::optional<HitResult> min_ray;
   
    std::shared_ptr <acgm::Ray> ray;
    glm::vec3 direction;
    float bias = 0.001;
    ShaderInput input;

    float min;
    printf("Pred cyklom Scene");
    printf(" Models count: %d\n", models_.size());
    printf("Camera: %f %f %f", camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
  
    //! using OMP to parallelize rendering, default 4 threads for now
//#pragma omp parallel for private(i, row, column, min, input, ray, shadow_ray, ray_hit, shadow_ray_hit, direction)
    for (row = 0; row < renderer.GetResolution().y; row++)
    {
        for (column = 0; column < renderer.GetResolution().x; column++)
        {
            direction = glm::normalize(camera->GetForwardDirection() + x * camera->GetRightDirection() + y * camera->GetUpDirection());
            ray = std::make_shared<acgm::Ray>(camera->GetPosition(), direction, bias);
            
            min_ray->ray_param = 10000.f;

            int index = 0;
            
            //! Search for nearest intersect ray x model and shadow ray x model
            for (i = 0; i < models_.size(); i++)
            {
                ray_hit = models_.at(i)->Intersect(*ray);

                if (ray_hit == std::nullopt) continue;
             
                if (ray_hit->ray_param >= 0 && ray_hit->ray_param < min_ray->ray_param && ray_hit->ray_param > camera->GetZNear() && ray_hit->ray_param < camera->GetZFar())
                {
                    min_ray->ray_param = ray_hit->ray_param;
                    min_ray->normal = ray_hit->normal;
                    min_ray->point = ray_hit->point;
                    index = i;
                }
            }

            input.direction_to_light = light->GetDirectionToLight(min_ray->point);
            input.normal = min_ray->normal;
            input.point = min_ray->point;
            input.direction_to_eye = camera->GetPosition() - min_ray->point;
            input.light_intensity = light->GetIntensityAt(min_ray->point);

            min = 10000.0f;
            for (i = 0; i < models_.size(); i++)
            {
                // ! Cast Shadow Ray
                shadow_ray = std::make_shared<acgm::Ray>(input.point, input.direction_to_light, bias);
                shadow_ray_hit = models_.at(i)->Intersect(*shadow_ray);

                if (shadow_ray_hit == std::nullopt) continue;
                
                if (shadow_ray_hit->ray_param >= 0 && shadow_ray_hit->ray_param < min)
                {
                     min = shadow_ray_hit->ray_param;
                }
            }

            if (min_ray->ray_param < min)
            {
                input.is_point_in_shadow = true;
            }
            else input.is_point_in_shadow = false;
            
            renderer.SetPixel(column, renderer.GetResolution().y - row - 1, models_.at(index)->GetShader()->CalculateColor(input));

            x += dx;
        }
        y -= dy;
        x = -tan(camera->GetFovYRad() / 2.0f);
    }
    printf("Done rendering");
}
