#include <ACGM_RayTracer_lib/Camera.h>

//! Constructor for camera, computing right direction
acgm::Camera::Camera(const glm::vec3 &position, const glm::vec3 &up_direction, const glm::vec3 &forward_direction, 
    const float z_near, const float z_far, const float fov_y_rad):
    position_(position), up_direction_(up_direction), forward_direction_(forward_direction), fov_y_rad_(fov_y_rad), z_near_(z_near), z_far_(z_far)
{
    right_direction_ = glm::cross(forward_direction, up_direction);
}

glm::vec3 acgm::Camera::GetPosition() const
{
    return position_;
}

glm::vec3 acgm::Camera::GetForwardDirection() const
{
    return forward_direction_;
}

glm::vec3 acgm::Camera::GetUpDirection() const
{
    return up_direction_;
}

glm::vec3 acgm::Camera::GetRightDirection() const
{
    return right_direction_;
}

float acgm::Camera::GetFovYRad() const
{
    return fov_y_rad_;
}

float acgm::Camera::GetZNear() const
{
    return z_near_;
}

float acgm::Camera::GetZFar() const
{
    return z_far_;
}
