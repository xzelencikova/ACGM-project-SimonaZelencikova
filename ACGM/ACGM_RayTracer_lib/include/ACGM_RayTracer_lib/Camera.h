#pragma once

#include <glm/glm.hpp>

namespace acgm
{
  //! A Camera representation
  class Camera
  {
  public:
    //! Camera constructor
    explicit Camera(const glm::vec3 &position, const glm::vec3& up_direction, const glm::vec3& forward_direction, const float z_near, const float z_far, const float fov_y_rad);

    //! Get camera attributes
    glm::vec3 GetPosition() const;

    glm::vec3 GetUpDirection() const;    
    glm::vec3 GetForwardDirection() const;
    glm::vec3 GetRightDirection() const;

    float GetFovYRad() const;
    float GetZNear() const;
    float GetZFar() const;
    
  private:
    const glm::vec3 position_;
    
    const glm::vec3 up_direction_;
    const glm::vec3 forward_direction_;
    glm::vec3 right_direction_;

    float z_near_;
    float z_far_;
    float fov_y_rad_;
  };
}
