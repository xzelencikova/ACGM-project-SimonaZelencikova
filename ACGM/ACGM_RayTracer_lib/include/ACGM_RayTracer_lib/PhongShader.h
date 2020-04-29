#pragma once

#include <ACGM_RayTracer_lib/Shader.h>


namespace acgm
{
    //! Representation of phong shader
    class PhongShader:public Shader
    {
    public:
        //! Phong Shader constructor
        explicit PhongShader(const cogs::Color3f color, const float shininess, const float ambient, const float diffuse, const float specular, const float glossiness, 
            const float transparency, const float refractive_index);
        //! Calculate shader color
        virtual Color CalculateColor(const ShaderInput& input) const override;
        virtual float GetGlossiness() const override;

    private:
        //! Phong shader variables
        cogs::Color3f color_;
        float shininess_;
        float ambient_;
        float diffuse_;
        float specular_;
        //! Reflection variable
        float glossiness_;
        //! Trasparency variable
        float transparency_;
        float refractive_index_;
    };
}