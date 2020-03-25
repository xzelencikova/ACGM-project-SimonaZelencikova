#include "ACGM_RayTracer_lib/SunLight.h"


acgm::SunLight::SunLight(float intensity, glm::vec3 direct):Light(intensity)
{
	this->direction = direct;
}

glm::vec3 acgm::SunLight::GetDirectionToLight(const glm::vec3& point) const
{
	return direction;
}

float acgm::SunLight::GetIntensityAt(const glm::vec3& point) const
{
	return GetIntensity();
}
