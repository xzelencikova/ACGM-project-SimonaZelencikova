#include "ACGM_RayTracer_lib/PhongShader.h"

acgm::PhongShader::PhongShader(cogs::Color3f color, float shininess,
    float ambient, float diffuse, float specular)
{
    this->color = color;
    this->shininess = shininess;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

float acgm::PhongShader::GetShininess()
{
    return shininess;
}

float acgm::PhongShader::GetAmbient()
{
    return ambient;
}

float acgm::PhongShader::GetDiffuse()
{
    return diffuse;
}

float acgm::PhongShader::GetSpecular()
{
    return specular;
}

cogs::Color3f acgm::PhongShader::CalculateColor(const ShaderInput& input) const
{
    // ! Calculate cosine angle and Phong Diffuse Shading
    float size_normal = pow(input.normal.x, 2) + pow(input.normal.y, 2) + pow(input.normal.z, 2);
    float size_light_direction = pow(input.direction_to_light.x, 2) + pow(input.direction_to_light.y, 2) + pow(input.direction_to_light.z, 2);
    float cosine_angle = glm::acos(glm::dot(input.direction_to_light, input.normal) / (sqrt(size_light_direction) * sqrt(size_normal)));
    float diffuse_phong = diffuse * input.light_intensity * cosine_angle;

    // ! Calculate Blinn-Phong Specular Shading
    glm::vec3 half_vector = glm::normalize(input.direction_to_eye + input.direction_to_light);
    float specular_phong = specular * input.light_intensity * pow(glm::dot(input.normal, half_vector), shininess);

    return acgm::Shader::CalculateColor(input) * (ambient + diffuse_phong + specular_phong);
}
