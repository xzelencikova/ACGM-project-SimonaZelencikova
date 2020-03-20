#pragma once
#include <glm/glm.hpp>
#include "Plane.h"


namespace acgm
{
  //! Representation of a ray
  class Ray
  {
  public:
      explicit Ray(glm::vec3 orig, glm::vec3 direct);

      glm::vec3 GetOrigin();
      glm::vec3 GetDirection();

      float Intersection(std::shared_ptr<acgm::Plane> plane);
      bool IntersectionWithTriangle(glm::vec3 &positionX, glm::vec3 &positionY, glm::vec3 &positionZ);
  private:
      glm::vec3 origin;
      glm::vec3 direction;
  };
}
