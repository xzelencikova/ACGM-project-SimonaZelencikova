#pragma once
#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/Light.h>

namespace acgm
{
    //! Representation of sun light
    class SunLight : public Light
    {
    public:
        explicit SunLight(const float intensity, const glm::vec3 direction, const glm::vec3 position);

        virtual glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;
        virtual float GetIntensityAt(const glm::vec3& point) const override;

    private:
        glm::vec3 direction_;
    };
}
