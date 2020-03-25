#include "ACGM_RayTracer_lib/Light.h"


acgm::Light::Light(float intensity):intensity(intensity)
{
}

float acgm::Light::GetIntensity() const
{
	return intensity;
}

glm::vec3 acgm::Light::GetDirectionToLight(const glm::vec3& point) const
{
	return point;
}

float acgm::Light::GetIntensityAt(const glm::vec3& point) const
{
	return intensity;
}