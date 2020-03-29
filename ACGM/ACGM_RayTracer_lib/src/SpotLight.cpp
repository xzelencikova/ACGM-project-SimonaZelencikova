#include "ACGM_RayTracer_lib/SpotLight.h"

acgm::SpotLight::SpotLight(float intensity, glm::vec3 position, float range,
	float linear_atten, float quadratic_atten, glm::vec3 spot_direction,
	float cutoff_angle, float exponent):PointLight(intensity, position, range, linear_atten, quadratic_atten)
{
	this->spot_direction = spot_direction;
	this->cutoff_angle = cutoff_angle;
	this->exponent = exponent;
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

glm::vec3 acgm::SpotLight::GetDirectionToLight(const glm::vec3& point) const
{
	return acgm::PointLight::GetDirectionToLight(point);
}

float acgm::SpotLight::GetIntensityAt(const glm::vec3& point) const
{
	float point_intensity = acgm::PointLight::GetIntensityAt(point);
	glm::vec3 light_direction = GetDirectionToLight(point);

	float size_spot_direction = pow(spot_direction.x, 2) + pow(spot_direction.y, 2) + pow(spot_direction.z, 2);
	float size_light_direction = pow(light_direction.x, 2) + pow(light_direction.y, 2) + pow(light_direction.z, 2);
	float angle = glm::acos(glm::dot(spot_direction, -light_direction) / (sqrt(size_spot_direction) * sqrt(size_light_direction))) * 180 / 3.14;

	//printf("%f ", angle);

	//if (angle > cutoff_angle) {
//		return 0.0f;
	//}

	float decay = 1 - pow((angle / cutoff_angle), exponent);
	return point_intensity * decay;
}
