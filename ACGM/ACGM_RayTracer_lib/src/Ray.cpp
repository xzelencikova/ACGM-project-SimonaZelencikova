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
std::optional<glm::vec3> acgm::Ray::GetRefractionDirection(const float index_of_refraction, const float index_of_refraction2, glm::vec3& normal) const
{
    float cos_direction = glm::dot(direction_, normal);
    float ior;

    //! Decide, if it's goind inside or outside of the object
    if (cos_direction < 0)
    {
        ior = index_of_refraction / index_of_refraction2;
        cos_direction = -cos_direction;
    }
    else
    {
        normal = -normal;
        ior = index_of_refraction2 / index_of_refraction;
    }

    float pow_ior = ior * ior;
    float cos_refract = 1 - pow_ior * (1 - cos_direction * cos_direction);
    //! If it's internal reflection, return std::nullopt
    if (cos_refract < 0)
    {
        return std::nullopt;
    }

    float cos_refracted_direction = std::sqrt(cos_refract);
    return ior * direction_ + normal * (ior * cos_direction - cos_refracted_direction);
}

// Reflected and refracted ray directions inspired by https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
