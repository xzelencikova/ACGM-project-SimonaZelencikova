#pragma once

#include <glm/common.hpp>

namespace acgm
{
  //! A Camera representation
  class Camera
  {
  public:
    //! Camera constructor
    Camera(
      const glm::vec3 &position,
      const glm::vec3 &target);

    //! Get camera position
    const glm::vec3 &GetPosition() const;
    const glm::vec3 &GetTarget() const;
    
    glm::vec3 &GetV();
    glm::vec3 &GetU();
    glm::vec3 &GetW();
    
    void SetCameraVectors(glm::vec3 v);

  private:
    //! Position in the scene
    const glm::vec3 position_;
    //! Target - the point the camera looks at
    const glm::vec3 target_;
    
    glm::vec3 v;
    glm::vec3 u;
    glm::vec3 w;
    // #TODO Add other camera parameters
  };
}
