#include <ACGM_RayTracer_lib/Scene.h>
#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/Plane.h>
#include <omp.h>



acgm::Scene::Scene()
{
    camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

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

                    std::shared_ptr < acgm::Camera> cameraLight = std::make_shared<acgm::Camera>(glm::vec3(column, 0.0f, -7.0f), glm::vec3(column, 1.0f, -7.0f));
                    glm::vec3 directionToLight = glm::normalize(cameraLight->GetU() + x * cameraLight->GetW() + y * cameraLight->GetV());
                    std::shared_ptr < acgm::Ray> rayLight = std::make_shared<acgm::Ray>(cameraLight->GetPosition(), directionToLight);

                    float intersectToLight = rayLight->IntersectionWithTriangle(bunny.GetBunny().points->GetPositions()[vertX], bunny.GetBunny().points->GetPositions()[vertY], bunny.GetBunny().points->GetPositions()[vertZ]);
                    float ambient = 0.1;

                    if(intersect < intersectToLight)
                    {
                        renderer.SetPixel(row, column, bunny.Color() * ambient);
                    }
                    else 
                    {
                        ambient = ambient + (1 - ambient) * (2 / intersect);
                        renderer.SetPixel(row, column, bunny.Color() * ambient);
                    }
                }
            }

            x += dx;
        }
        y -= dy;
        x = -tan(radian / 2.);
    }
}
