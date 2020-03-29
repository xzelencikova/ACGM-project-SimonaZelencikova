#include "ACGM_RayTracer_lib/PhongShader.h"
#include <regex>

acgm::PhongShader::PhongShader(cogs::Color3f color, float shininess,
    float ambient, float diffuse, float specular): Shader(color)
{
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
    // ! Calculate Phong Ambient Shading
    cogs::Color3f ambient_phong;

    //// ! Calculate cosine angle and Phong Diffuse Shading
    float size_normal = sqrt(pow(input.normal.x, 2) + pow(input.normal.y, 2) + pow(input.normal.z, 2));
    float size_light_direction = sqrt(pow(input.direction_to_light.x, 2) + pow(input.direction_to_light.y, 2) + pow(input.direction_to_light.z, 2));
    float cosine_angle = glm::dot(input.normal, input.direction_to_light) / (size_light_direction * size_normal);

    cogs::Color3f diffuse_phong = Shader::CalculateColor(input) * diffuse * input.light_intensity * cosine_angle;

    // ! Calculate Blinn-Phong Specular Shading
    glm::vec3 half_vector = glm::normalize(input.direction_to_eye + input.direction_to_light);
    cogs::Color3f specular_phong = cogs::Color3f(1.0f, 1.0f, 1.0f) * specular * input.light_intensity * pow(glm::dot(input.normal, half_vector), shininess);

    if (input.is_point_in_shadow) {
        ambient_phong = Shader::CalculateColor(input) * ambient;
        return ambient_phong * input.light_intensity * cosine_angle;
    }
    else ambient_phong = Shader::CalculateColor(input) * (ambient + ((1 - ambient) * input.light_intensity));

    return diffuse_phong + specular_phong; //ambient_phong; + diffuse_phong + specular_phong;
}
