#pragma once
#include <glm/glm.hpp>

namespace acgm
{
    //! Representation of a ray
    class SpotLight
    {
    public:
        explicit SpotLight(float intensity, glm::vec3 position, float range,
            float linear_atten, float quadratic_atten, glm::vec3 spot_direction,
            float cutoff_angle, float exponent);

        float GetIntensity();
        glm::vec3 GetPosition();
        float GetRange();
        float GetLinearAttenuation();
        float GetQuadraticAttenuation();
        glm::vec3 GetSpotDirection();
        float GetCutoffAngle();
        float GetExponent();

    private:
        float intensity;
        glm::vec3 position;
        float range;
        float linear_attenuation;
        float quadratic_attenuation;
        glm::vec3 spot_direction;
        float cutoff_angle;
        float exponent;
    };
}
