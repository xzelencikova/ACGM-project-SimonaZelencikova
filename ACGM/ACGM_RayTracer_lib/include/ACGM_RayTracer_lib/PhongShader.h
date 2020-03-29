#pragma once
//#include <COGS/Color.h>
//#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/Shader.h>

namespace acgm
{
    //! Representation of phong shader
    class PhongShader:public Shader
    {
    public:
        explicit PhongShader(cogs::Color3f color, float shininess, 
            float ambient, float diffuse, float specular);

        float GetShininess();
        float GetAmbient();
        float GetDiffuse();
        float GetSpecular();

        virtual cogs::Color3f CalculateColor(const ShaderInput& input) const override;

    private:
        float shininess;
        float ambient;
        float diffuse;
        float specular;
    };
}