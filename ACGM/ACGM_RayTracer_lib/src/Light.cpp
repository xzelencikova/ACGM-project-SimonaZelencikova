#include "ACGM_RayTracer_lib/Light.h"


//! Base light constructor
acgm::Light::Light(const float intensity, const glm::vec3 position): 
	intensity_(intensity), position_(position)
{
}

glm::vec3 acgm::Light::GetPosition() const
{
	return position_;
}

//! Base functions for direction and intensity
glm::vec3 acgm::Light::GetDirectionToLight(const glm::vec3& point) const
{
	return point;
}

float acgm::Light::GetIntensityAt(const glm::vec3& point) const
{
	return intensity_;
}