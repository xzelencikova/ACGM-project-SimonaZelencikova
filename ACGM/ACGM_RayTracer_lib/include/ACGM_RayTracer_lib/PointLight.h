#pragma once
#include <glm/glm.hpp>

namespace acgm
{
    //! Representation of a ray
    class PointLight
    {
    public:
        explicit PointLight(float intensity, glm::vec3 position, float range, float linear_atten, float quadratic_atten);

        float GetIntensity();
        glm::vec3 GetPosition();
        float GetRange();
        float GetLinearAttenuation();
        float GetQuadraticAttenuation();

    private:
        float intensity;
        glm::vec3 position;
        float range;
        float linear_attenuation;
        float quadratic_attenuation;
    };
}
