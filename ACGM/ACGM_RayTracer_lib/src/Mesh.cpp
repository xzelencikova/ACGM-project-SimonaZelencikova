#include <ACGM_RayTracer_lib/Mesh.h>

#include <ACGM_RayTracer_lib/Triangle.h>

acgm::Mesh::Mesh(std::string file_name, glm::mat4 transform, std::string name):file_name(file_name), transform(transform), Model(name)
{
    printf("%s\n", file_name);
	mesh_obj.Import(file_name);
	mesh_obj.points->Transform(transform);
    printf("%d\n", mesh_obj.faces->GetFaceCount());
    for (int i = 0; i < 4; i++) printf("%f %f %f %f\n", transform[i].x, transform[i].y, transform[i].z, transform[i].w);
}

std::optional<acgm::HitResult> acgm::Mesh::Intersect(acgm::Ray & ray) const
{
    std::optional<HitResult> min_hit;
    min_hit->ray_param = 10000.0f;
    std::optional<HitResult> hit;

    for (int j = 0; j < mesh_obj.faces->GetFaceCount(); j++)
    {
        Triangle triangle = Triangle(mesh_obj.points->GetPositions()[mesh_obj.faces->GetFaces()[j].x], mesh_obj.points->GetPositions()[mesh_obj.faces->GetFaces()[j].y], mesh_obj.points->GetPositions()[mesh_obj.faces->GetFaces()[j].z]);

        hit = triangle.Intersect(ray);

        if (hit == std::nullopt) continue;


        if (hit->ray_param > 0 && hit->ray_param < min_hit->ray_param)
        {
            min_hit->ray_param = hit->ray_param;
            min_hit->normal = hit->normal;
            min_hit->point = hit->point;
        }
    }
    return min_hit;
}
