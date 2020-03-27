#include<ACGM_RayTracer_lib/Triangle.h>

acgm::Triangle::Triangle(const glm::vec3 vertexX, const glm::vec3 vertexY, const glm::vec3 vertexZ):
	vertexX(vertexX), vertexY(vertexY), vertexZ(vertexZ)
{
}

std::optional<acgm::HitResult> acgm::Triangle::Intersect(acgm::Ray & ray) const
{
    glm::vec3 edge1, edge2, h, s, q;
    float a, f, u, v;

    edge1 = vertexY - vertexX;
    edge2 = vertexZ - vertexX;
    
    h = glm::cross(ray.GetDirection(), edge2);
    a = glm::dot(edge1, h);

    if (a == 0)
        return std::nullopt;    // This ray is parallel to this triangle.

    f = 1.0 / a;
    s = ray.GetOrigin() - vertexX;
    u = f * glm::dot(s, h);
    
    if (u <= 0.0 || u > 1.0)
        return std::nullopt;

    q = glm::cross(s, edge1);
    v = f * glm::dot(ray.GetDirection(), q);

    if (v <= 0.0 || u + v > 1.0)
        return std::nullopt;
    // At this stage we can compute t to find out where the intersection point is on the line.
    HitResult hit;
    
    hit.ray_param = f * glm::dot(edge2, q);
    hit.normal = glm::cross(vertexY - vertexX, vertexZ - vertexX);
    hit.point = ray.GetPoint(hit.ray_param) + (hit.normal * ray.GetBias());

    return hit;
}