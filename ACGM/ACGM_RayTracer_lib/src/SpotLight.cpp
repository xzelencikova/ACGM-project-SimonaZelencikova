#include "ACGM_RayTracer_lib/SpotLight.h"

#define ANGLE 180.0f
#define PI 3.1415927


//! Spot light constructor
acgm::SpotLight::SpotLight(const float intensity, const glm::vec3 position, const float range, const float linear_attenuation, 
	const float quadratic_attenuation, const glm::vec3 spot_direction, const float cutoff_angle, const float exponent):
	PointLight(intensity, position, range, linear_attenuation, quadratic_attenuation), 
	spot_direction_(spot_direction), cutoff_angle_(cutoff_angle), exponent_(exponent)
{
}

//! Calculate direction and intensity for spot light at point 
glm::vec3 acgm::SpotLight::GetDirectionToLight(const glm::vec3& point) const
{
	return acgm::PointLight::GetDirectionToLight(point);
}

float acgm::SpotLight::GetIntensityAt(const glm::vec3& point) const
{
	float point_intensity = acgm::PointLight::GetIntensityAt(point);
	glm::vec3 light_direction = GetDirectionToLight(point);

	//! Calculate sizes of vectors and angle between direction vectors
	float size_spot_direction = pow(spot_direction_.x, 2) + pow(spot_direction_.y, 2) + pow(spot_direction_.z, 2);
	float size_light_direction = pow(light_direction.x, 2) + pow(light_direction.y, 2) + pow(light_direction.z, 2);
	float alpha = glm::acos(glm::dot(spot_direction_, -light_direction) / (sqrt(size_spot_direction) * sqrt(size_light_direction)));
	alpha = abs(alpha * ANGLE / PI);

	if (alpha > cutoff_angle_) {
		return 0.0f;
	}

	float decay = 1 - pow(alpha / float(cutoff_angle_), exponent_);
	return point_intensity * decay;
}
