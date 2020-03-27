#pragma once
#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/Light.h>

namespace acgm
{
    //! Representation of a ray
    class SunLight : public Light
    {
    public:
        explicit SunLight(float intensity, glm::vec3 direct);

        virtual glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;
        virtual float GetIntensityAt(const glm::vec3& point) const override;

    private:
        glm::vec3 direction;
    };
}
