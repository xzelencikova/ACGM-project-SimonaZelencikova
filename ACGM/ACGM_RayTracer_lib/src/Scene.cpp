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
    
    std::optional<HitResult> ray_hit;
    std::optional<HitResult> shadow_ray_hit;
    float min;
    std::shared_ptr <acgm::Ray> ray;
    glm::vec3 direction;
    float bias = 0.001;
    printf("Pred cyklom Scene");
    printf(" Models count: %d\n", models_.size());
  
    //! using OMP to parallelize rendering, default 4 threads for now
//#pragma omp parallel for private(i, row, column, t, min) shared(direction, ray, renderer, x, y)
    for (row = 0; row < renderer.GetResolution().y; row++)
    {
        for (column = 0; column < renderer.GetResolution().x; column++)
        {
            direction = glm::normalize(camera->GetForwardDirection() + x * camera->GetRightDirection() + y * camera->GetUpDirection());
            ray = std::make_shared<acgm::Ray>(camera->GetPosition(), direction, bias);
            min = 10000.0f;
            
            //! Search for nearest intersect ray x model and shadow ray x model
            for (i = 0; i < models_.size(); i++)
            {
                ShaderInput input;
                // printf("Model %d", i);

                ray_hit = models_.at(i)->Intersect(*ray);

                if (ray_hit == std::nullopt) continue;
             
                if (ray_hit->ray_param > 0 && ray_hit->ray_param < min) 
                {

                    input.direction_to_light = light->GetDirectionToLight(ray_hit->point);
                    input.light_intensity = light->GetIntensityAt(ray_hit->point);
                    input.normal = ray_hit->normal;
                    input.point = ray_hit->point;
                    input.direction_to_eye = ray_hit->point - ray->GetOrigin();
                    // ! Cast Shadow Ray
                    std::shared_ptr <acgm::Ray> shadow_ray = std::make_shared<acgm::Ray>(input.point, glm::normalize(input.direction_to_light), bias);
                    shadow_ray_hit = models_.at(i)->Intersect(*shadow_ray);

                    if (shadow_ray_hit == std::nullopt) continue;

                    min = ray_hit->ray_param;

                    if (ray_hit->ray_param < shadow_ray_hit->ray_param)
                    {
                        input.is_point_in_shadow = true;
                    }
                    else input.is_point_in_shadow = false;

                    renderer.SetPixel(row, column, models_.at(i)->GetShader()->CalculateColor(input));
                }
            }

            min = 10000.0f;

            x += dx;
        }
        y -= dy;
        x = -tan(camera->GetFovYRad() / 2.);
    }
    printf("Done rendering");
}
