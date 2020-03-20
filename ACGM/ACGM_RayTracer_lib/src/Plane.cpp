#include <ACGM_RayTracer_lib/Plane.h>


acgm::Plane::Plane(glm::vec3 plane_pt, glm::vec3 plane_norm, const cogs::Color3f& color):Model(color) 
{
	plane_point = plane_pt;
	plane_normal = plane_norm;
}

glm::vec3 acgm::Plane::GetPlanePoint() 
{ 
	return plane_point; 
}

glm::vec3 acgm::Plane::GetPlaneNormal() 
{ 
	return plane_normal; 
}
