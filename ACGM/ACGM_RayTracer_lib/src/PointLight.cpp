#include "ACGM_RayTracer_lib/PointLight.h"

acgm::PointLight::PointLight(float intensity, glm::vec3 position, float range, float linear_atten, float quadratic_atten)
{
	this->intensity = intensity;
	this->position = position;
	this->range = range;
	this->linear_attenuation = linear_atten;
	this->quadratic_attenuation = quadratic_atten;
}

float acgm::PointLight::GetIntensity()
{
	return intensity;
}

glm::vec3 acgm::PointLight::GetPosition()
{
	return position;
}

float acgm::PointLight::GetRange()
{
	return range;
}

float acgm::PointLight::GetLinearAttenuation()
{
	return linear_attenuation;
}

float acgm::PointLight::GetQuadraticAttenuation()
{
	return quadratic_attenuation;
}
