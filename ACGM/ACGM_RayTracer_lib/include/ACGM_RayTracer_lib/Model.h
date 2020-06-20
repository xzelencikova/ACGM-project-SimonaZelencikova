#pragma once

#include <Utils/Dialogs.h>

#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/Shader.h>

namespace acgm
{
    //! Structure for values od ray hit
    struct HitResult {
        glm::vec3 normal;
        glm::vec3 point;
        float ray_param;
        glm::vec2 uv;
    };
    //! Model  - abstract base class for scene models
    class Model
    {
    public:
        //! Model constructor
        explicit Model(const std::string name);
        virtual ~Model() = default;

        //! Set shader for model method
        void SetShader(const std::shared_ptr<acgm::Shader> shader);
    
        //! Get shader method
        std::shared_ptr<acgm::Shader> GetShader() const;
        //! Model intersection with ray base method
        virtual std::optional<acgm::HitResult> Intersect(std::shared_ptr<acgm::Ray>& ray) const;

    private:
        //! Model name and shader
        const std::string name_;
        std::shared_ptr<acgm::Shader> shader_;
    };
}
