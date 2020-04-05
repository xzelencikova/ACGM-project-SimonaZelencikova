#pragma once
#include <glm/glm.hpp>

namespace acgm
{
    //! Representation of light
    class Light
    {
    public:
        //! Light base constructor
        explicit Light(const float intensity, const glm::vec3 position);
        virtual ~Light() = default;

        //! Getter for position of light
        glm::vec3 GetPosition() const;
        
        //! Get direction to light and intensity at point methods
        virtual glm::vec3 GetDirectionToLight(const glm::vec3& point) const;
        virtual float GetIntensityAt(const glm::vec3& point) const;

    private:
        //! Light intensity and position values
        const float intensity_;
        const glm::vec3 position_;
    };
}
