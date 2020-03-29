#include "ACGM_RayTracer_lib/PointLight.h"
#include <cmath>

//! Point Light constructor
acgm::PointLight::PointLight(const float intensity, const glm::vec3 position, const float range, const float linear_attenuation, const float quadratic_attenuation) :
	Light(intensity, position), range_(range), linear_attenuation_(linear_attenuation), quadratic_attenuation_(quadratic_attenuation)
{
}

//! Calculate direction and intensity of point light at point
glm::vec3 acgm::PointLight::GetDirectionToLight(const glm::vec3& point) const
{
	glm::vec3 position = acgm::Light::GetPosition();
	return glm::vec3( position.x - point.x, position.y - point.y, position.z - point.z);
}

float acgm::PointLight::GetIntensityAt(const glm::vec3& point) const
{
	glm::vec3 position = acgm::Light::GetPosition();
	float distance = glm::distance(position, point);
	
	float power_range = pow(range_, 2);
	float l = range_ / (range_ + (distance * linear_attenuation_));
	float q = power_range / (power_range + (pow(distance, 2) * quadratic_attenuation_));
	
	return Light::GetIntensityAt(point) * l * q;
}
