#pragma once
#include <COGS/Color.h>
#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/Shader.h>

namespace acgm
{
    //! Representation of abstract shader
    class PhongShader:Shader
    {
    public:
        explicit PhongShader(cogs::Color3f color, float shininess, 
            float ambient, float diffuse, float specular);

        float GetShininess();
        float GetAmbient();
        float GetDiffuse();
        float GetSpecular();

        cogs::Color3f CalculateColor(const ShaderInput& input) const;

    private:
        cogs::Color3f color;
        float shininess;
        float ambient;
        float diffuse;
        float specular;
    };
}