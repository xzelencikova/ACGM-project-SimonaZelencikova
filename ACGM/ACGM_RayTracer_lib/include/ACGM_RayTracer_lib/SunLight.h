#pragma once
#include <glm/glm.hpp>

namespace acgm
{
    //! Representation of a ray
    class SunLight
    {
    public:
        explicit SunLight(float intensity, glm::vec3 direct);

        float GetIntensity();
        glm::vec3 GetDirection();

    private:
        float intensity;
        glm::vec3 direction;
    };
}
