#pragma once

#include <vector>
#include <HIRO_DRAW/renderers/RasterRenderer.h>

// #TODO: To begin with, the scene will contain one camera and a vector of models
#include <ACGM_RayTracer_lib/Camera.h>
#include <ACGM_RayTracer_lib/Model.h>
#include <ACGM_RayTracer_lib/Ray.h>


namespace acgm
{
  //! Scene representation
  class Scene
  {
  public:
    // #TODO Initialize a Scene object
    Scene();
    ~Scene() = default;

    //! RayTrace the scene
    void Raytrace(hiro::draw::RasterRenderer &renderer, acgm::Model &bunny) const;

  private:
    // #TODO Add one camera and a vector of models
      Camera *camera;

    // FYI: The models have to be smart pointers (such as std::shared_ptr<...>)
      std::vector<std::shared_ptr<acgm::Model>> models_;
  };
}
