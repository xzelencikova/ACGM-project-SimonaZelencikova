#include "ACGM_RayTracer_lib/PointLight.h"
#include <cmath>

acgm::PointLight::PointLight(float intensity, glm::vec3 position, float range, float linear_atten, float quadratic_atten) :
	Light(intensity, position)
{
	this->range = range;
	this->linear_attenuation = linear_atten;
	this->quadratic_attenuation = quadratic_atten;
}

//glm::vec3 acgm::PointLight::GetPosition()
//{
//	return acgm::Light::GetPosition();
//}

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

glm::vec3 acgm::PointLight::GetDirectionToLight(const glm::vec3& point) const
{
	glm::vec3 position = acgm::Light::GetPosition();
	return glm::vec3( position.x - point.x, position.y - point.y, position.z - point.z);
}

float acgm::PointLight::GetIntensityAt(const glm::vec3& point) const
{
	glm::vec3 position = acgm::Light::GetPosition();
	float distance = glm::distance(position, point);
	
	float power_range = pow(range, 2);
	float l = range / (range + (distance * linear_attenuation));
	float q = power_range / (power_range + (pow(distance, 2) * quadratic_attenuation));
	
	return Light::GetIntensityAt(point) * l * q;
}
