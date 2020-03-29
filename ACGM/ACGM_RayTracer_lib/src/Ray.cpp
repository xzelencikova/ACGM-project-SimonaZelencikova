#include <ACGM_RayTracer_lib/Ray.h>


//! Ray constructor
acgm::Ray::Ray(glm::vec3 origin, glm::vec3 direction, const float bias):
    origin_(origin), direction_(direction), bias_(bias)
{
}

glm::vec3 acgm::Ray::GetOrigin() const
{ 
	return origin_; 
}

glm::vec3 acgm::Ray::GetDirection() const 
{ 
	return direction_; 
}

float acgm::Ray::GetBias() const
{
    return bias_;
}

//! Compute intersection point between ray and model
glm::vec3 acgm::Ray::GetPoint(const float t) const
{
    return origin_ + (t * direction_);
}
