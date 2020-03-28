#include <ACGM_RayTracer_lib/Ray.h>


// #TODO Implement your functionality here
acgm::Ray::Ray(glm::vec3 orig, glm::vec3 direct, const float bias):
    origin(orig), direction(direct), bias(bias)
{
}

glm::vec3 acgm::Ray::GetOrigin() 
{ 
	return origin; 
}

glm::vec3 acgm::Ray::GetDirection() 
{ 
	return direction; 
}

glm::vec3 acgm::Ray::GetPoint(const float t)
{
    return origin + (t * direction);
}

float acgm::Ray::GetBias()
{
    return bias;
}
