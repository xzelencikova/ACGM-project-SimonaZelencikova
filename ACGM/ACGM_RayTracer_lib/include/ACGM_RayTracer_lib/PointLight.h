#pragma once
#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/Light.h>

namespace acgm
{
    //! Representation of a point light
    class PointLight: public Light
    {
    public:
        explicit PointLight(float intensity, glm::vec3 position, float range, float linear_atten, float quadratic_atten);

        glm::vec3 GetPosition();
        float GetRange();
        float GetLinearAttenuation();
        float GetQuadraticAttenuation();

        glm::vec3 GetDirectionToLight(const glm::vec3& point) const;
        float GetIntensityAt(const glm::vec3& point) const;

    private:
        glm::vec3 position;
        float range;
        float linear_attenuation;
        float quadratic_attenuation;
    };
}
