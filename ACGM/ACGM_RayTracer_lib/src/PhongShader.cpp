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

cogs::Color3f acgm::PhongShader::GetColor()
{
    return color;
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
