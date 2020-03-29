#include <ACGM_RayTracer_lib/Mesh.h>
#include <ACGM_RayTracer_lib/Triangle.h>

//#include <ACGM_RayTracer_lib/Triangle.h>

acgm::Mesh::Mesh(std::string file_name, glm::mat4 transform, std::string name):file_name(file_name), transform(transform), Model(name)
{
    // mesh import a transform.. mesh_obj je typu Cogs::Mesh
	mesh_obj.Import(file_name);
	mesh_obj.points->Transform(transform);
    printf("%d\n", mesh_obj.faces->GetFaceCount());
}

std::optional<acgm::HitResult> acgm::Mesh::Intersect(std::shared_ptr<acgm::Ray>& ray) const
{
    std::optional<HitResult> min_hit;
    min_hit->ray_param = 10000.0f;
    std::optional<HitResult> hit;
    int j;

 #pragma omp parallel for private(j)//min, input, ray, shadow_ray, ray_hit, shadow_ray_hit, direction)
    for (j = 0; j < mesh_obj.faces->GetFaceCount(); j++)
    {
        // Nastavím si indexy vrcholov
        glm::uint vertX = mesh_obj.faces->GetFaces()[j].x;
        glm::uint vertY = mesh_obj.faces->GetFaces()[j].y;
        glm::uint vertZ = mesh_obj.faces->GetFaces()[j].z;
        // vytvorím trojuholník s tromi vrcholmi
        Triangle triangle = Triangle(mesh_obj.points->GetPositions()[vertX], mesh_obj.points->GetPositions()[vertY], mesh_obj.points->GetPositions()[vertZ]);
        // zavolám intersect pre každý trojuholník
        //float t = ray->Intersection(mesh_obj.points->GetPositions()[vertX], mesh_obj.points->GetPositions()[vertY], mesh_obj.points->GetPositions()[vertZ]);
        float t = triangle.Intersect(ray);

        //if (hit == std::nullopt) continue;

        // h¾adám najmenší intersect
        if (t > 0 && t < min_hit->ray_param)
        {
    //        printf("x %f %f %f\n", mesh_obj.points->GetPositions()[vertX].x, mesh_obj.points->GetPositions()[vertX].y, mesh_obj.points->GetPositions()[vertX].z);
      //      printf("y %f %f %f\n", mesh_obj.points->GetPositions()[vertY].x, mesh_obj.points->GetPositions()[vertY].y, mesh_obj.points->GetPositions()[vertY].z);
        //    printf("z %f %f %f\n", mesh_obj.points->GetPositions()[vertZ].x, mesh_obj.points->GetPositions()[vertZ].y, mesh_obj.points->GetPositions()[vertZ].z);
          //  printf("t %f\n", hit->ray_param);
            min_hit->ray_param = t;
            min_hit->normal = glm::cross(mesh_obj.points->GetPositions()[vertY] - mesh_obj.points->GetPositions()[vertX], mesh_obj.points->GetPositions()[vertZ] - mesh_obj.points->GetPositions()[vertX]);;
            min_hit->point = ray->GetPoint(min_hit->ray_param) + (min_hit->normal * ray->GetBias());
        }
    }
    return min_hit;
}
