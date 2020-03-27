#pragma once
#include <glm/glm.hpp>

namespace acgm
{
    //! Representation of a light
    class Light
    {
    public:
        explicit Light(float intensity);
        virtual ~Light() = default;

        float GetIntensity() const;
        virtual glm::vec3 GetDirectionToLight(const glm::vec3& point) const;
        virtual float GetIntensityAt(const glm::vec3& point) const;

    private:
        float intensity;
    };
}
