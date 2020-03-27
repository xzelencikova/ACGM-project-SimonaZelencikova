#pragma once
#include <COGS/Color.h>
#include <glm/glm.hpp>

namespace acgm
{
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
        explicit Shader(cogs::Color3f color);

        void SetShaders(const std::shared_ptr<Shader> shader0, const std::shared_ptr<Shader> shader1);

        virtual cogs::Color3f CalculateColor(const ShaderInput& input) const;

    private:
        cogs::Color3f color;
    };
}