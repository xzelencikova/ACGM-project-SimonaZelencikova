#include <ACGM_RayTracer_lib/Scene.h>
#include <omp.h>


acgm::Scene::Scene(const std::shared_ptr<acgm::Camera>& camera, const std::shared_ptr<acgm::Light>& light, const std::vector<std::shared_ptr<acgm::Model>>& models) : 
    models_(models), camera(camera), light(light)
{
}

void acgm::Scene::Raytrace(hiro::draw::RasterRenderer &renderer) const
{
    int row;
    int column;
    int i;

    float y;
    y = tan(camera->GetFovYRad() / 2.0f);
    float x = -y;
    
    float dy = 2 * tan(camera->GetFovYRad() / 2.0f) / float(renderer.GetResolution().y);
    float dx = 2 * tan(camera->GetFovYRad() / 2.0f) / float(renderer.GetResolution().x);
    
    std::shared_ptr <acgm::Ray> shadow_ray;
    std::optional<HitResult> ray_hit;
    std::optional<HitResult> shadow_ray_hit;
    std::optional<HitResult> min_ray;
    std::optional<HitResult> min_s_ray;

    std::shared_ptr <acgm::Ray> ray;
    glm::vec3 direction;
    float bias = 0.001;
    ShaderInput input;

    float min;
    int index;
  
    //! using OMP to parallelize rendering, default 4 threads for now
//#pragma omp parallel for private(row, column, i,/*, ray, shadow_ray, ray_hit, direction, input*/) shared(x, y, index)//min, input, ray, shadow_ray, ray_hit, shadow_ray_hit, direction)
    for (row = 0; row < renderer.GetResolution().y; row++)
    {
        for (column = 0; column < renderer.GetResolution().x; column++)
        {
            direction = glm::normalize(camera->GetForwardDirection() + x * camera->GetRightDirection() + y * camera->GetUpDirection());
            ray = std::make_shared<acgm::Ray>(camera->GetPosition(), direction, bias);

            index = -1;
            min_ray->ray_param = 10000.0f;

            //! Search for nearest intersect ray x model and shadow ray x model
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
         
            input.direction_to_light =  glm::normalize(light->GetDirectionToLight(min_ray->point));
            input.normal = glm::normalize(min_ray->normal);
            input.point = min_ray->point;
            input.direction_to_eye = glm::normalize(camera->GetPosition() - min_ray->point);
            input.light_intensity = light->GetIntensityAt(min_ray->point);
            shadow_ray = std::make_shared<acgm::Ray>(input.point, input.direction_to_light, bias);

            min = 10000.0f;

            for (i = 0; i < models_.size(); i++)
            {
                // ! Cast Shadow Ray
                shadow_ray_hit = models_.at(i)->Intersect(shadow_ray);
                
                if (shadow_ray_hit->ray_param > 0 && shadow_ray_hit->ray_param < min)
                {
                     min = shadow_ray_hit->ray_param;
                     min_s_ray->normal = shadow_ray_hit->normal;
                     min_s_ray->point = shadow_ray_hit->point;
                }
            }
            
            float get_distance = glm::distance(input.point, light->GetPosition());

            if (min < get_distance)
            {
                input.is_point_in_shadow = true;
            }
            else input.is_point_in_shadow = false;

            if (index > -1)
                renderer.SetPixel(column, renderer.GetResolution().y - row - 1, models_.at(index)->GetShader()->CalculateColor(input));

            x += dx;
        }
        y -= dy;
        x = -tan(camera->GetFovYRad() / 2.0f);
    }
    printf("Done rendering");
}
