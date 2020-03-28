#include<ACGM_RayTracer_lib/Triangle.h>

acgm::Triangle::Triangle(const glm::vec3 vertexX, const glm::vec3 vertexY, const glm::vec3 vertexZ):
	vertexX(vertexX), vertexY(vertexY), vertexZ(vertexZ)
{
}

float acgm::Triangle::Intersect(std::shared_ptr<acgm::Ray> ray) const
{
    glm::vec3 edge1, edge2, h, s, q;
    float a, f, u, v;

    edge1 = vertexY - vertexX;
    edge2 = vertexZ - vertexX;

    //printf("Edge1: %f %f %f\n", edge1.x, edge1.y, edge1.z);
    //printf("Edge2: %f %f %f\n", edge2.x, edge2.y, edge2.z);

    h = glm::cross(ray->GetDirection(), edge2);
    a = glm::dot(edge1, h);

    //printf("h: %f %f %f\n", h.x, h.y, h.z);
    //printf("a: %f\n", a);

    if (a == 0)
        return -1;    // This ray is parallel to this triangle.

    f = 1.0 / a;
    s = ray->GetOrigin() - vertexX;
    u = f * glm::dot(s, h);

    //printf("f: %f\n", f);
    //printf("s: %f %f %f\n", s.x, s.y, s.z);
    //printf("u: %f\n", u);

    if (u <= 0.0 || u > 1.0)
        return -1;
    q = glm::cross(s, edge1);
    v = f * glm::dot(ray->GetDirection(), q);

    if (v <= 0.0f || (u + v) > 1.0f)
        return -1;
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * glm::dot(edge2, q);

    //printf("Edge1: %f %f %f\n", edge1.x, edge1.y, edge1.z);
    //printf("Edge2: %f %f %f\n", edge2.x, edge2.y, edge2.z);

    //printf("h: %f %f %f\n", h.x, h.y, h.z);
    //printf("a: %f\n", a);

    //printf("f: %f\n", f);
    //printf("s: %f %f %f\n", s.x, s.y, s.z);
    //printf("u: %f\n", u);

    //printf("q: %f %f %f\n", q.x, q.y, q.z);
    //printf("v: %f\n", v);
    //printf("t: %f\n", t);

    return t;
}