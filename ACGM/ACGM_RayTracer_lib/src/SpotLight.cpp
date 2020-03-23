#include "ACGM_RayTracer_lib/SpotLight.h"

acgm::SpotLight::SpotLight(float intensity, glm::vec3 position, float range,
	float linear_atten, float quadratic_atten, glm::vec3 spot_direction,
	float cutoff_angle, float exponent)
{
	this->intensity = intensity;
	this->position = position;
	this->range = range;
	this->linear_attenuation = linear_atten;
	this->quadratic_attenuation = quadratic_atten;
	this->spot_direction = spot_direction;
	this->cutoff_angle = cutoff_angle;
	this->exponent = exponent;
}

float acgm::SpotLight::GetIntensity()
{
	return intensity;
}

glm::vec3 acgm::SpotLight::GetPosition()
{
	return position;
}

float acgm::SpotLight::GetRange()
{
	return range;
}

float acgm::SpotLight::GetLinearAttenuation()
{
	return linear_attenuation;
}

float acgm::SpotLight::GetQuadraticAttenuation()
{
	return quadratic_attenuation;
}

glm::vec3 acgm::SpotLight::GetSpotDirection()
{
	return spot_direction;
}

float acgm::SpotLight::GetCutoffAngle()
{
	return cutoff_angle;
}

float acgm::SpotLight::GetExponent()
{
	return exponent;
}