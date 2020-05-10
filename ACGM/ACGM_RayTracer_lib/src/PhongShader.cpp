#include "ACGM_RayTracer_lib/PhongShader.h"


//! PhongShader constructor
acgm::PhongShader::PhongShader(const cogs::Color3f color, const float shininess, const float ambient, const float diffuse, const float specular, const float glossiness, 
    const float transparency, const float refractive_index):
    color_(color), shininess_(shininess), ambient_(ambient), diffuse_(diffuse), specular_(specular), glossiness_(glossiness), transparency_(transparency),
    refractive_index_(refractive_index)
{
}

//! Calculate color for the point
acgm::Color acgm::PhongShader::CalculateColor(const ShaderInput& input) const
{
    Color color;
    color.glossiness = glossiness_;
    color.transparency = transparency_;
    color.refractive_index = refractive_index_;

    //! Calculate and return Phong Ambient Shading, if point is in shadow
    if (input.is_point_in_shadow) {
        color.color = color_ * ambient_;
        return color;
    }

    //! Calculate cosine angle
    float size_normal = sqrt(input.normal.x * input.normal.x + input.normal.y * input.normal.y + input.normal.z * input.normal.z);
    float size_light_direction = sqrt(input.direction_to_light.x * input.direction_to_light.x + input.direction_to_light.y * input.direction_to_light.y + input.direction_to_light.z * input.direction_to_light.z);
    float cosine_angle = glm::dot(input.normal, input.direction_to_light) / (size_light_direction * size_normal);
    //! Calculate Phong Diffuse Shading
    float diffuse_phong = diffuse_ * input.light_intensity * cosine_angle;

    //! Calculate Blinn-Phong Specular Shading
    glm::vec3 half_vector = glm::normalize(input.direction_to_eye + input.direction_to_light);
    float normal_half_exp = pow(glm::dot(input.normal, half_vector), shininess_);
    cogs::Color3f specular_phong = cogs::Color3f(1.0f, 1.0f, 1.0f) * specular_ * input.light_intensity * normal_half_exp;

    color.color = (diffuse_phong + ambient_) * color_ + specular_phong;
    return color;
}
