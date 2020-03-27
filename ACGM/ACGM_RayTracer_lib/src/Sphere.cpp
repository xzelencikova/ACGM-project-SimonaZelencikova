#include <glm/geometric.hpp>
#include <glm/gtc/epsilon.hpp>
#include <ACGM_RayTracer_lib/Sphere.h>



acgm::Sphere::Sphere(const glm::vec3 &position, float radius, std::string name)
  : Model(name), position_(position), radius_(radius)
{
}

std::optional<acgm::HitResult> acgm::Sphere::Intersect(acgm::Ray & ray) const
{
  glm::vec3 oo = ray.GetOrigin() - position_;

  float A = glm::dot(ray.GetDirection(), ray.GetDirection());
  float B = -2.0f * glm::dot(oo, ray.GetDirection());
  float C = glm::dot(oo, oo) - radius_ * radius_;
  float D = B * B - 4.0f * A * C;

  if (D < 0)
  {
    return std::nullopt;
  }

  float sD = glm::sqrt(D);

  float t1 = 0.5 * (B + sD) / A;
  if (t1 < ray.GetBias())
  {
    t1 = INFINITY;
  }

  float t2 = 0.5 * (B - sD) / A;
  if (t2 < ray.GetBias())
  {
    t2 = INFINITY;
  }

  const float t = glm::min(t1, t2);
  if (glm::isinf(t) || t < 0.0f)
  {
    return std::nullopt;
  }

  HitResult hit;
  //! Set hit params of sphere and ray intersection
  hit.ray_param = t;
  hit.normal = glm::normalize(ray.GetPoint(t) - position_);
  hit.point = ray.GetPoint(hit.ray_param);
  
  return hit;
}

const glm::vec3 &acgm::Sphere::GetPosition() const
{
  return position_;
}

float acgm::Sphere::GetRadius() const
{
  return radius_;
}

