#include "ACGM_RayTracer_lib/PhongShader.h"


//! PhongShader constructor
acgm::PhongShader::PhongShader(const cogs::Color3f color, const float shininess, const float ambient, const float diffuse, const float specular, const float glossiness):
    color_(color), shininess_(shininess), ambient_(ambient), diffuse_(diffuse), specular_(specular), glossiness_(glossiness)
{
}

//! Calculate color for the point
cogs::Color3f acgm::PhongShader::CalculateColor(const ShaderInput& input) const
{
    //! Calculate cosine angle
    float size_normal = sqrt(pow(input.normal.x, 2) + pow(input.normal.y, 2) + pow(input.normal.z, 2));
    float size_light_direction = sqrt(pow(input.direction_to_light.x, 2) + pow(input.direction_to_light.y, 2) + pow(input.direction_to_light.z, 2));
    float cosine_angle = glm::dot(input.normal, input.direction_to_light) / (size_light_direction * size_normal);

    float ambient_phong;

    //! Calculate and return Phong Ambient Shading, if point is in shadow
    if (input.is_point_in_shadow) {
        ambient_phong = ambient_ * cosine_angle;
        return color_ * ambient_phong;
    }
    else ambient_phong = (ambient_ + (1 - ambient_) * input.light_intensity) * cosine_angle/2;

    //! Calculate Phong Diffuse Shading
    float diffuse_phong = diffuse_ * input.light_intensity * cosine_angle;

    //! Calculate Blinn-Phong Specular Shading
    glm::vec3 half_vector = glm::normalize(input.direction_to_eye + input.direction_to_light);
    float normal_half_exp = pow(glm::dot(input.normal, half_vector), shininess_);
    cogs::Color3f specular_phong = cogs::Color3f(1.0f, 1.0f, 1.0f) * specular_ * input.light_intensity * normal_half_exp;

    return (diffuse_phong + ambient_phong) * color_ + specular_phong;
}
