#pragma once
#include <glm/glm.hpp>

namespace acgm
{
    //! Representation of light
    class Light
    {
    public:
        explicit Light(const float intensity, const glm::vec3 position);
        virtual ~Light() = default;

        glm::vec3 GetPosition() const;
        
        virtual glm::vec3 GetDirectionToLight(const glm::vec3& point) const;
        virtual float GetIntensityAt(const glm::vec3& point) const;

    private:
        const float intensity_;
        const glm::vec3 position_;
    };
}
