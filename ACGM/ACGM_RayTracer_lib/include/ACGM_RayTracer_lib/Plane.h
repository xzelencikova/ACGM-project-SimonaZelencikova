#pragma once

#include <ACGM_RayTracer_lib/Model.h>

namespace acgm
{
  //! Plane representation
  class Plane : public Model
  {
  public:
      Plane(const glm::vec3 plane_pt, const glm::vec3 plane_norm, const std::string name);
      virtual ~Plane() = default;

      glm::vec3 GetPlanePoint();
      glm::vec3 GetPlaneNormal();
      virtual std::optional<acgm::HitResult> Intersect(std::shared_ptr<acgm::Ray>& ray) const override;

  private:
      glm::vec3 plane_point;
      glm::vec3 plane_normal;
  };
}
