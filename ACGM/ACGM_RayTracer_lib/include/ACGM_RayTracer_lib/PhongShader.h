#pragma once

#include <ACGM_RayTracer_lib/Shader.h>


namespace acgm
{
    //! Representation of phong shader
    class PhongShader:public Shader
    {
    public:
        //! Phong Shader constructor
        explicit PhongShader(const cogs::Color3f color, const float shininess, const float ambient, const float diffuse, const float specular, const float glossiness);
        //! Calculate shader color
        virtual cogs::Color3f CalculateColor(const ShaderInput& input) const override;

    private:
        //! Phong shader variables
        cogs::Color3f color_;
        float shininess_;
        float ambient_;
        float diffuse_;
        float specular_;
        //! Reflection variable
        float glossiness_;
    };
}