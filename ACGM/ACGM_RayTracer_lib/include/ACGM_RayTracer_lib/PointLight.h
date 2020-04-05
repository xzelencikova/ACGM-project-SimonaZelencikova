#pragma once
#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/Light.h>

namespace acgm
{
    //! Representation of point light
    class PointLight: public Light
    {
    public:
        //! PointLight constructor
        explicit PointLight(const float intensity, const glm::vec3 position, const float range, const float linear_attenuation, const float quadratic_attenuation);

        //! Get direction to light and intensity at point methods
        virtual glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;
        virtual float GetIntensityAt(const glm::vec3& point) const override;

    private:
        //! PointLight range
        const float range_;
        //! PointLight linear and quadratic attenuations
        const float linear_attenuation_;
        const float quadratic_attenuation_;
    };
}
