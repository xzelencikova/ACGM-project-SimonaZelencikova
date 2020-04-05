#include <ACGM_RayTracer_lib/Plane.h>

//! Plane constructor
acgm::Plane::Plane(glm::vec3 point, glm::vec3 normal, std::string name) : 
    Model(name), point_(point), normal_(normal)
{
}

//! Calculate intersection params between ray and plane
std::optional<acgm::HitResult> acgm::Plane::Intersect(std::shared_ptr<acgm::Ray>& ray) const
{
    float dot2 = glm::dot(ray->GetDirection(), normal_);
    //! Denominator can't be 0
    if (dot2 < FLT_EPSILON && dot2 > -FLT_EPSILON)
    {
        return std::nullopt;
    }

    //! Set hit params of plane and ray intersection
    HitResult hit;

    hit.ray_param = glm::dot((point_ - ray->GetOrigin()), normal_) / dot2;
    hit.normal = normal_;
    hit.point = ray->GetPoint(hit.ray_param) + (normal_ * ray->GetBias());;

    return hit;
}
