#pragma once

#include <ACGM_RayTracer_lib/Model.h>



namespace acgm
{
  //! Plane representation
  class Plane : public Model
  {
  public:
      explicit Plane(glm::vec3 plane_pt, glm::vec3 plane_norm, const cogs::Color3f& color);

      glm::vec3 GetPlanePoint();
      glm::vec3 GetPlaneNormal();
  private:
      glm::vec3 plane_point;
      glm::vec3 plane_normal;
  };
}
