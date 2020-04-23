#pragma once
#include <glm/glm.hpp>


namespace acgm
{
    //! Representation of a ray
    class Ray
    {
    public:
        //! Ray attribute
        explicit Ray(glm::vec3 orig, glm::vec3 direct, const float bias);

        //! Getters for ray attributes
        glm::vec3 GetOrigin() const;
        glm::vec3 GetDirection() const;
        float GetBias() const;
        glm::vec3 GetPoint(const float t) const;
        glm::vec3 GetReflectionDirection(const glm::vec3 &normal) const;

    private:
        //! Ray origin and direction vectors and bias value
        const glm::vec3 origin_;
        const glm::vec3 direction_;
        const float bias_;
  };
}
