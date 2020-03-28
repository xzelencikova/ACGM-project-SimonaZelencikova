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

std::optional<acgm::HitResult> acgm::Mesh::TriangleIntersect(glm::vec3& vertexX, glm::vec3& vertexY, glm::vec3& vertexZ, std::shared_ptr<acgm::Ray> & ray) const
{
    glm::vec3 edge1, edge2, h, s, q;
    float a, f, u, v;

    edge1 = vertexY - vertexX;
    edge2 = vertexZ - vertexX;

    h = glm::cross(ray->GetDirection(), edge2);
    a = glm::dot(edge1, h);

    if (a == 0)
        return std::nullopt;    // This ray is parallel to this triangle.

    f = 1.0f / a;
    s = ray->GetOrigin() - vertexX;
    u = f * glm::dot(s, h);

    if (u <= 0.0 || u > 1.0)
        return std::nullopt;

    q = glm::cross(s, edge1);
    v = f * glm::dot(ray->GetDirection(), q);

    if (v <= 0.0f || (u + v) > 1.0f)
        return std::nullopt;
    // At this stage we can compute t to find out where the intersection point is on the line.
    HitResult hit;

    hit.ray_param = f * glm::dot(edge2, q);
    hit.normal = glm::cross(vertexY - vertexX, vertexZ - vertexX);
    hit.point = ray->GetPoint(hit.ray_param) + (hit.normal * ray->GetBias());
    /*printf("edge1 %f %f %f\n", edge1.x, edge1.y, edge1.z);
    printf("edge2 %f %f %f\n", edge2.x, edge2.y, edge2.z);
    printf("h %f %f %f\n", h.x, h.y, h.z);
    printf("a %f\n", a);
    printf("f %f\n", f);
    printf("s %f %f %f\n", s.x, s.y, s.z);
    printf("u %f\n", u);
    printf("q %f %f %f\n", q.x, q.y, q.z);
    printf("v %f\n", v);
    printf("t %f\n", hit.ray_param);*/

 //   printf("%f %f %f\n", vertexX.x, vertexX.y, vertexX.z);
   // printf("Hit: %f\n", hit.ray_param);
    return hit;
}
