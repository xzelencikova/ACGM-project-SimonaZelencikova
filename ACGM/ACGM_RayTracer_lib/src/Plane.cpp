#include <ACGM_RayTracer_lib/Plane.h>


acgm::Plane::Plane(glm::vec3 plane_pt, glm::vec3 plane_norm, std::string name) : Model(name), plane_point(plane_pt), plane_normal(plane_norm)
{
}

glm::vec3 acgm::Plane::GetPlanePoint() 
{ 
	return plane_point; 
}

glm::vec3 acgm::Plane::GetPlaneNormal() 
{ 
	return plane_normal; 
}

std::optional<acgm::HitResult> acgm::Plane::Intersect(acgm::Ray &ray) const
{
    float dot2 = glm::dot(ray.GetDirection(), plane_normal);

    if (dot2 == 0)
    {
        return std::nullopt;
    }
    HitResult hit;
//    ! Set hit params of plane and ray intersection
    hit.ray_param = glm::dot((plane_point - ray.GetOrigin()), plane_normal) / dot2;
    hit.normal = plane_normal;
    hit.point = ray.GetPoint(hit.ray_param);

   // printf("%f ", hit.ray_param);

    return hit;
}