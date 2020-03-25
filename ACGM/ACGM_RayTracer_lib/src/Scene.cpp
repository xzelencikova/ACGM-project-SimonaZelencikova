#include <ACGM_RayTracer_lib/Scene.h>
#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/Plane.h>
#include <omp.h>


acgm::Scene::Scene()
{
    camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    light = new SunLight(1, glm::vec3(0.421076, -0.842152, -0.336861));

    std::shared_ptr<acgm::Plane> plane_left = std::make_shared<acgm::Plane>(glm::vec3(0,1,0), glm::vec3(0,-1,0), cogs::Color3f(0.9f, 0.0f, 0.1f));
    std::shared_ptr<acgm::Plane> plane_right = std::make_shared<acgm::Plane>(glm::vec3(0, -1, 0), glm::vec3(0, 1, 0), cogs::Color3f(0.0f, 0.8f, 0.9f));
    std::shared_ptr<acgm::Plane> plane_back = std::make_shared<acgm::Plane>(glm::vec3(0, 0, -5), glm::vec3(0, 0, 1), cogs::Color3f(0.5f, 0.5f, 0.5f));
    std::shared_ptr<acgm::Plane> plane_up = std::make_shared<acgm::Plane>(glm::vec3(1, 0, 0), glm::vec3(-1, 0, 0), cogs::Color3f(0.7f, 0.7f, 0.7f));
    std::shared_ptr<acgm::Plane> plane_down = std::make_shared<acgm::Plane>(glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0), cogs::Color3f(0.9f, 0.9f, 0.9f));

    models_.reserve(7);
    models_.push_back(plane_up);
    models_.push_back(plane_down);
    models_.push_back(plane_back);
    models_.push_back(plane_right);
    models_.push_back(plane_left);
}

void acgm::Scene::Raytrace(hiro::draw::RasterRenderer &renderer, acgm::Model &bunny) const
{
    int row;
    int column;
    int i;

    float radian = glm::radians(45.0f);
    float y = tan(radian / 2.);
    float x = -y;
    
    camera->SetCameraVectors(glm::vec3(0, 1, 0));

    float dy = 2 * tan(radian / 2.) / 500.0f;
    float dx = 2 * tan(radian / 2.) / 500.0f;
    float t;
    float min;
    Ray* ray;
    glm::vec3 direction;

  
    //! using OMP to parallelize rendering, default 4 threads for now
//#pragma omp parallel for private(i, row, column, t, min) shared(direction, ray, renderer, x, y)
    for (row = 0; row < renderer.GetResolution().y; row++)
    {
        for (column = 0; column < renderer.GetResolution().x; column++)
        {
            direction = glm::normalize(camera->GetU() + x * camera->GetW() + y * camera->GetV());
            ray = new Ray(camera->GetPosition(), direction);
            min = 10000.0f;
            
            //! Search for nearest intersect ray x plane
            for (i = 0; i < models_.size(); i++)
            {
                std::shared_ptr<acgm::Plane> plane = (std::dynamic_pointer_cast<acgm::Plane>)(models_.at(i));
                t = ray->Intersection(plane);
             
                if (t >= 0 && t < min) 
                {
                    float intensity = 1.5 / t;
                    min = t;
                    std::shared_ptr<acgm::Model> model = models_.at(i);
                    renderer.SetPixel(row, column, model->Color() * intensity);
                }
            }

            min = 10000.0f;

            for (int j = 0; j < bunny.GetBunny().faces->GetFaceCount(); j++)
            {
                glm::uint vertX = bunny.GetBunny().faces->GetFaces()[j].x;
                glm::uint vertY = bunny.GetBunny().faces->GetFaces()[j].y;
                glm::uint vertZ = bunny.GetBunny().faces->GetFaces()[j].z;
                
                float intersect = ray->IntersectionWithTriangle(bunny.GetBunny().points->GetPositions()[vertX], bunny.GetBunny().points->GetPositions()[vertY], bunny.GetBunny().points->GetPositions()[vertZ]);

                if (intersect > 0 && intersect < min)
                {
                    min = intersect;
                    float min_light_i = 10000;

                    // compute intersection point
                    glm::vec3 intersection_point = camera->GetPosition() + (min * ray->GetDirection());
                    glm::vec3 triangle_norm = glm::cross(bunny.GetBunny().points->GetPositions()[vertY] - bunny.GetBunny().points->GetPositions()[vertX], bunny.GetBunny().points->GetPositions()[vertZ] - bunny.GetBunny().points->GetPositions()[vertX]);
                    intersection_point = intersection_point + (triangle_norm * 0.0001f);
                    float ambient = 0.5;
                    
                    for (int shadow = 0; shadow < bunny.GetBunny().faces->GetFaceCount(); shadow++) {
                        glm::uint vertNewX = bunny.GetBunny().faces->GetFaces()[shadow].x;
                        glm::uint vertNewY = bunny.GetBunny().faces->GetFaces()[shadow].y;
                        glm::uint vertNewZ = bunny.GetBunny().faces->GetFaces()[shadow].z;

                        // create shadow light
                        std::shared_ptr < acgm::Ray> rayLight = std::make_shared<acgm::Ray>(intersection_point, glm::normalize(light->GetDirectionToLight(intersection_point)));
                        float intersect_to_light = rayLight->IntersectionWithTriangle(bunny.GetBunny().points->GetPositions()[vertNewX], bunny.GetBunny().points->GetPositions()[vertNewY], bunny.GetBunny().points->GetPositions()[vertNewZ]);
                        if (intersect_to_light > 0 && intersect_to_light < min_light_i)
                        {
                            min_light_i = intersect_to_light;

                            // find if the triangle is in shadow
                            if (intersect >= intersect_to_light)
                            {
                                ambient = ambient + ((1 - ambient) * light->GetIntensityAt(intersection_point));
                            }
                        }
                    }
                    renderer.SetPixel(row, column, bunny.Color() * ambient);
                }
            }

            x += dx;
        }
        y -= dy;
        x = -tan(radian / 2.);
    }
}
