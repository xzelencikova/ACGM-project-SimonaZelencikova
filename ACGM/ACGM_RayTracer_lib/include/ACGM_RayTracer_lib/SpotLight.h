#pragma once
#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/PointLight.h>

namespace acgm
{
    //! Representation of a ray
    class SpotLight : public PointLight
    {
    public:
        explicit SpotLight(float intensity, glm::vec3 position, float range,
            float linear_atten, float quadratic_atten, glm::vec3 spot_direction,
            float cutoff_angle, float exponent);

        glm::vec3 GetSpotDirection();
        float GetCutoffAngle();
        float GetExponent();

        glm::vec3 GetDirectionToLight(const glm::vec3& point) const;
        float GetIntensityAt(const glm::vec3& point) const;

    private:
        glm::vec3 spot_direction;
        float cutoff_angle;
        float exponent;
    };
}
