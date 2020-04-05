#pragma once
#include <ACGM_RayTracer_lib\Shader.h>



namespace acgm
{
    //! Representation of checker shader
    class CheckerShader: public Shader
    {
    public:
        //! Checker Shader constructor
        explicit CheckerShader(const float cube_size, const std::shared_ptr<Shader> shader0, const std::shared_ptr<Shader> shader1);
        //! Calculate shader color
        virtual cogs::Color3f CalculateColor(const ShaderInput& input) const override;

    private:
        //! Shader cube size and shaders
        float cube_size_;
        std::shared_ptr<Shader> shader0_;
        std::shared_ptr<Shader> shader1_;
    };
}
