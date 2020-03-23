#include "ACGM_RayTracer_lib/SunLight.h"


acgm::SunLight::SunLight(float intensity, glm::vec3 direct)
{
	this->intensity = intensity;
	this->direction = direct;
}

float acgm::SunLight::GetIntensity()
{
	return intensity;
}

glm::vec3 acgm::SunLight::GetDirection()
{
	return direction;
}
