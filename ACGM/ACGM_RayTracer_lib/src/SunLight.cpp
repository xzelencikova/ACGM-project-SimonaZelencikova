#include "ACGM_RayTracer_lib/SunLight.h"

//! SunLight Constructor
acgm::SunLight::SunLight(const float intensity, const glm::vec3 direction, const glm::vec3 position):
	Light(intensity, position), direction_(direction)
{
}

//! Get intensity at point and direction from point to light 
glm::vec3 acgm::SunLight::GetDirectionToLight(const glm::vec3& point) const
{
	return -direction_;
}

float acgm::SunLight::GetIntensityAt(const glm::vec3& point) const
{
	return acgm::Light::GetIntensityAt(point);
}
