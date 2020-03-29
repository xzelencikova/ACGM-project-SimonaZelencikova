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
        explicit PhongShader(const cogs::Color3f color, const float shininess, const float ambient, const float diffuse, const float specular);

        virtual cogs::Color3f CalculateColor(const ShaderInput& input) const override;

    private:
        float shininess_;
        float ambient_;
        float diffuse_;
        float specular_;
    };
}