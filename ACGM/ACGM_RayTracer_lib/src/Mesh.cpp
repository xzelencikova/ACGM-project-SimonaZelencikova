#include <ACGM_RayTracer_lib/Mesh.h>

#include <ACGM_RayTracer_lib/Triangle.h>

acgm::Mesh::Mesh(std::string file_name, glm::mat4 transform, std::string name):file_name(file_name), transform(transform), Model(name)
{
    // mesh import a transform.. mesh_obj je typu Cogs::Mesh
	mesh_obj.Import(file_name);
	mesh_obj.points->Transform(transform);
    printf("%d\n", mesh_obj.faces->GetFaceCount());
}

std::optional<acgm::HitResult> acgm::Mesh::Intersect(acgm::Ray & ray) const
{
    std::optional<HitResult> min_hit;
    min_hit->ray_param = 10000.0f;
    std::optional<HitResult> hit;

    for (int j = 0; j < mesh_obj.faces->GetFaceCount(); j++)
    {
        // Nastavím si indexy vrcholov
        int vertX = mesh_obj.faces->GetFaces()[j].x;
        int vertY = mesh_obj.faces->GetFaces()[j].y;
        int vertZ = mesh_obj.faces->GetFaces()[j].z;
        // vytvorím trojuholník s tromi vrcholmi
        Triangle triangle = Triangle(mesh_obj.points->GetPositions()[vertX], mesh_obj.points->GetPositions()[vertY], mesh_obj.points->GetPositions()[vertZ]);
        // zavolám intersect pre každý trojuholník
        hit = triangle.Intersect(ray);

        if (hit == std::nullopt) continue;

        // h¾adám najmenší intersect
        if (hit->ray_param > 0 && hit->ray_param < min_hit->ray_param)
        {
            min_hit->ray_param = hit->ray_param;
            min_hit->normal = hit->normal;
            min_hit->point = hit->point;
        }
    }
    return min_hit;
}
