#pragma once
#include <COGS/Color.h>
#include <glm/glm.hpp>

namespace acgm
{
    //! structure for shader input
    struct ShaderInput
    {
        glm::vec3 point;
        glm::vec3 normal;
        glm::vec3 direction_to_eye;
        glm::vec3 direction_to_light;
        float light_intensity;
        bool is_point_in_shadow;
    };

    //! Representation of a shader
    class Shader
    {
    public:
        Shader();
        ~Shader() = default;
        explicit Shader(const cogs::Color3f color);

        virtual cogs::Color3f CalculateColor(const ShaderInput& input) const;

    private:
        cogs::Color3f color_;
    };
}