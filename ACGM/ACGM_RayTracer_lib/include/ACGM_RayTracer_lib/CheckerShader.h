#pragma once
#include <glm/glm.hpp>
#include <ACGM_RayTracer_lib\PhongShader.h>

namespace acgm
{
    //! Representation of a ray
    class CheckerShader: Shader
    {
    public:
        explicit CheckerShader(float cube_size, const PhongShader &shader0, const PhongShader &shader1);

        float GetCubeSize();

        cogs::Color3f CalculateColor(const ShaderInput& input) const;

    private:
        float cube_size;
        const PhongShader shader0;
        const PhongShader shader1;
    };
}