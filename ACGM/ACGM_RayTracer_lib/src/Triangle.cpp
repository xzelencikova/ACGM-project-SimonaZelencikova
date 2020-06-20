#include<ACGM_RayTracer_lib/Triangle.h>



//! Triangle constructor
acgm::Triangle::Triangle(const glm::vec3 vertex_x, const glm::vec3 vertex_y, const glm::vec3 vertex_z):
	vertex_x_(vertex_x), vertex_y_(vertex_y), vertex_z_(vertex_z)
{
}

//! Getters  for triangle vertexes
glm::vec3 acgm::Triangle::GetVertexX() const
{
    return vertex_x_;
}

glm::vec3 acgm::Triangle::GetVertexY() const
{
    return vertex_y_;
}

glm::vec3 acgm::Triangle::GetVertexZ() const
{
    return vertex_z_;
}

//! Intersection between triangle and ray, @ https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
std::optional<acgm::HitResult> acgm::Triangle::Intersect(std::shared_ptr<acgm::Ray> ray) const
{
    glm::vec3 edge1, edge2, h, s, q;
    float a, f, u, v;

    edge1 = vertex_y_ - vertex_x_;
    edge2 = vertex_z_ - vertex_x_;

    h = glm::cross(ray->GetDirection(), edge2);
    a = glm::dot(edge1, h);

    //! Ray is parallel to this triangle
    if (a > -FLT_EPSILON && a < FLT_EPSILON)
        return std::nullopt;

    f = 1.0 / a;
    s = ray->GetOrigin() - vertex_x_;
    u = f * glm::dot(s, h);

    if (u <= 0.0 || u > 1.0)
        return std::nullopt;
    
    q = glm::cross(s, edge1);
    v = f * glm::dot(ray->GetDirection(), q);

    if (v <= 0.0f || (u + v) > 1.0f)
        return std::nullopt;

    acgm::HitResult hit;
    hit.ray_param = f * glm::dot(edge2, q);
    hit.uv = glm::vec2(u, v);
    //! Return intersection
    return hit;
}