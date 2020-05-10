#pragma once
#include <glm/glm.hpp>
#include <COGS/Color.h>


namespace acgm
{
    //! Structure for shader input
    struct ShaderInput
    {
        glm::vec3 point;
        glm::vec3 normal;
        glm::vec3 direction_to_eye;
        glm::vec3 direction_to_light;
        float light_intensity;
        bool is_point_in_shadow;
    };
    //! Structure for color and the attributes for reflectíon and refraction
    struct Color
    {
        cogs::Color3f color;
        float glossiness;
        float transparency;
        float refractive_index;
    };

    //! Representation of a shader
    class Shader
    {
    public:
        //! Shader constructor
        explicit Shader();
        virtual ~Shader() = default;

        //! Calculate shader color
        virtual Color CalculateColor(const ShaderInput& input) const = 0;
    };
}