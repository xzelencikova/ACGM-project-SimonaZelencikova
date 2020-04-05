#pragma once
#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/Light.h>

namespace acgm
{
    //! Representation of sun light
    class SunLight : public Light
    {
    public:
        //! SunLight constructor
        explicit SunLight(const float intensity, const glm::vec3 direction, const glm::vec3 position);

        //! Get direction to light and intensity at point method
        virtual glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;
        virtual float GetIntensityAt(const glm::vec3& point) const override;

    private:
        //! Direction of sun light
        glm::vec3 direction_;
    };
}
