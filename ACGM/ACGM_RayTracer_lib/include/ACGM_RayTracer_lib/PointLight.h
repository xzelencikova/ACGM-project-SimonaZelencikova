#pragma once
#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/Light.h>

namespace acgm
{
    //! Representation of point light
    class PointLight: public Light
    {
    public:
        explicit PointLight(const float intensity, const glm::vec3 position, const float range, const float linear_attenuation, const float quadratic_attenuation);

        virtual glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;
        virtual float GetIntensityAt(const glm::vec3& point) const override;

    private:
        const float range_;
        const float linear_attenuation_;
        const float quadratic_attenuation_;
    };
}
