#pragma once
#include <glm/glm.hpp>


namespace acgm
{
  //! Representation of a ray
  class Ray
  {
  public:
      explicit Ray(glm::vec3 orig, glm::vec3 direct, const float bias);

      glm::vec3 GetOrigin();
      glm::vec3 GetDirection();
      glm::vec3 GetPoint(const float t);
      float GetBias();
      float acgm::Ray::Intersection(glm::vec3& positionX, glm::vec3& positionY, glm::vec3& positionZ);

  private:
      glm::vec3 origin;
      glm::vec3 direction;
      const float bias;
  };
}
