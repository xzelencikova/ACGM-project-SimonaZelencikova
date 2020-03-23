#pragma once
#include <COGS/Color.h>
#include <glm/glm.hpp>

namespace acgm
{
    //! Representation of a phong shader
    class PhongShader
    {
    public:
        explicit PhongShader(cogs::Color3f color, float shininess, 
            float ambient, float diffuse, float specular);

        cogs::Color3f GetColor();
        float GetShininess();
        float GetAmbient();
        float GetDiffuse();
        float GetSpecular();

    private:
        cogs::Color3f color;
        float shininess;
        float ambient;
        float diffuse;
        float specular;
    };
}