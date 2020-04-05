#pragma once
#include <glm/glm.hpp>
#include <COGS/Color.h>


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
        //! Shader constructor
        explicit Shader();
        virtual ~Shader() = default;

        //! Calculate shader color
        virtual cogs::Color3f CalculateColor(const ShaderInput& input) const;

    };
}