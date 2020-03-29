#pragma once
#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/PointLight.h>

namespace acgm
{
    //! Representation of spot light inheriting from point light
    class SpotLight : public PointLight
    {
    public:
        explicit SpotLight(const float intensity, const glm::vec3 position, const float range,
            const float linear_attenuation, const float quadratic_attenuation, const glm::vec3 spot_direction,
            const float cutoff_angle, const float exponent);

        virtual glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;
        virtual float GetIntensityAt(const glm::vec3& point) const override;

    private:
        const glm::vec3 spot_direction_;
        const float cutoff_angle_;
        const float exponent_;
    };
}
