#include <ACGM_RayTracer_lib/Ray.h>


//! Ray constructor
acgm::Ray::Ray(glm::vec3 origin, glm::vec3 direction, const float bias):
    origin_(origin), direction_(direction), bias_(bias)
{
}

glm::vec3 acgm::Ray::GetOrigin() const
{ 
	return origin_; 
}

glm::vec3 acgm::Ray::GetDirection() const 
{ 
	return direction_; 
}

float acgm::Ray::GetBias() const
{
    return bias_;
}

//! Compute intersection point between ray and model
glm::vec3 acgm::Ray::GetPoint(const float t) const
{
    return origin_ + (t * direction_);
}

//! Calculate reflected direction of the ray
glm::vec3 acgm::Ray::GetReflectionDirection(const glm::vec3& normal) const
{
    float norm_direction_dot = glm::dot(direction_, normal);
    return -2 * norm_direction_dot * normal + direction_;
}

//! Calculate refracted direction of the ray
std::optional<glm::vec3> acgm::Ray::GetRefractionDirection(const float index_of_refraction, glm::vec3& normal) const
{
    float cos_direction = glm::dot(direction_, normal);

    if (cos_direction < 0)
    {
        cos_direction = -cos_direction;
    }
    else normal = -normal;

    float pow_ior = index_of_refraction * index_of_refraction;
    float cos_refract = 1 - pow_ior * (1 - cos_direction * cos_direction);
    if (cos_refract < 0)
    {
        return std::nullopt;
    }

    float cos_refracted_direction = std::sqrt(cos_refract);
    return index_of_refraction * direction_ + normal * (index_of_refraction * cos_direction - cos_refracted_direction);
}

// Reflected and refracted ray directions inspired by https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
