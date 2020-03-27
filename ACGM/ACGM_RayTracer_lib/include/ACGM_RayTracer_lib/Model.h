#pragma once

#include <Utils/Dialogs.h>

#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/Shader.h>

namespace acgm
{
  struct HitResult {
      glm::vec3 normal;
      glm::vec3 point;
      float ray_param;
  };
  //! Model  - abstract base class for scene models
  class Model
  {
  public:
    explicit Model(const std::string name);
    virtual ~Model() = default;

    std::string GetName();
    void SetShader(const std::shared_ptr<acgm::Shader> shader);
    
    std::shared_ptr<acgm::Shader> GetShader();
    virtual std::optional<acgm::HitResult> Intersect(acgm::Ray & ray) const;

  private:
    std::string name;
    std::shared_ptr<acgm::Shader> shader;
  };
}
