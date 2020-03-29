#pragma once
#include <ACGM_RayTracer_lib\Shader.h>

namespace acgm
{
    //! Representation of checker shader
    class CheckerShader: public Shader
    {
    public:
        explicit CheckerShader(const float cube_size, const std::shared_ptr<Shader> shader0, const std::shared_ptr<Shader> shader1);

        virtual cogs::Color3f CalculateColor(const ShaderInput& input) const override;

    private:
        float cube_size_;
        std::shared_ptr<Shader> shader0_;
        std::shared_ptr<Shader> shader1_;
    };
}