#include "ACGM_RayTracer_lib/Light.h"


acgm::Light::Light(float intensity, const glm::vec3 & position): intensity(intensity), position(position)
{
}

float acgm::Light::GetIntensity() const
{
	return intensity;
}

glm::vec3 acgm::Light::GetPosition() const
{
	return position;
}

glm::vec3 acgm::Light::GetDirectionToLight(const glm::vec3& point) const
{
	return point;
}

float acgm::Light::GetIntensityAt(const glm::vec3& point) const
{
	return intensity;
}