#include <ACGM_RayTracer_lib/Camera.h>
#include <glm\gtx\quaternion.hpp>



acgm::Camera::Camera(
  const glm::vec3 &position,
  const glm::vec3 &target): position_(position), target_(target)
{
}

const glm::vec3 &acgm::Camera::GetPosition() const
{
  return position_;
}

const glm::vec3& acgm::Camera::GetTarget() const
{
    return target_;
}

glm::vec3 &acgm::Camera::GetU()
{
    return u;
}

glm::vec3 &acgm::Camera::GetV()
{
    return v;
}

glm::vec3 &acgm::Camera::GetW()
{
    return w;
}

void acgm::Camera::SetCameraVectors(glm::vec3 v)
{
    this->v = v;
    this->u = target_ - position_;
    this->w = glm::cross(u, v);
}
