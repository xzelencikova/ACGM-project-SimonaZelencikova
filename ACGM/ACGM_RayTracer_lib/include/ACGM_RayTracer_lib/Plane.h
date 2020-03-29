#pragma once

#include <ACGM_RayTracer_lib/Model.h>

namespace acgm
{
  //! Plane representation
  class Plane : public Model
  {
  public:
      Plane(const glm::vec3 point, const glm::vec3 normal, const std::string name);
      virtual ~Plane() = default;

      virtual std::optional<acgm::HitResult> Intersect(std::shared_ptr<acgm::Ray>& ray) const override;

  private:
      glm::vec3 point_;
      glm::vec3 normal_;
  };
}
