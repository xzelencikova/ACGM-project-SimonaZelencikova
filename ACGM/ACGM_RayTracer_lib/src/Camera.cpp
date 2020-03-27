#include <ACGM_RayTracer_lib/Camera.h>

acgm::Camera::Camera(const glm::vec3 &position, const glm::vec3 &up_direction, const glm::vec3 &forward_direction, const float z_near, const float z_far, const float fov_y_rad):
    position_(position), up_direction(up_direction), forward_direction(forward_direction), fov_y_rad(fov_y_rad), z_near(z_near), z_far(z_far)
{
    right_direction = glm::cross(forward_direction, up_direction);
}

const glm::vec3 &acgm::Camera::GetPosition() const
{
  return position_;
}

glm::vec3 acgm::Camera::GetForwardDirection() const
{
    return forward_direction;
}

glm::vec3 acgm::Camera::GetUpDirection() const
{
    return up_direction;
}

glm::vec3 acgm::Camera::GetRightDirection() const
{
    return right_direction;
}

float acgm::Camera::GetFovYRad() const
{
    return fov_y_rad;
}