#pragma once
#include <glm/glm.hpp>
#include <ACGM_RayTracer_lib\PhongShader.h>

namespace acgm
{
    //! Representation of checker shader
    class CheckerShader: public Shader
    {
    public:
        explicit CheckerShader(float cube_size, const std::shared_ptr<Shader> shader0, const std::shared_ptr<Shader> shader1);

        float GetCubeSize();

        virtual cogs::Color3f CalculateColor(const ShaderInput& input) const override;

    private:
        float cube_size;
        std::shared_ptr<Shader> shader0;
        std::shared_ptr<Shader> shader1;
    };
}