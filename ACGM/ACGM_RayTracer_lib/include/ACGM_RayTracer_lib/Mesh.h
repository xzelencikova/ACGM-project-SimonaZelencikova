#pragma once

#include <COGS/Mesh.h>
#include <ACGM_RayTracer_lib/Triangle.h>
#include <ACGM_RayTracer_lib/Model.h>

namespace acgm
{
    //! Mesh representation
    class Mesh : public Model
    {
    public:
        explicit Mesh(const std::string file_name, const glm::mat4 transform, const std::string name);
        ~Mesh() = default;

        virtual std::optional<acgm::HitResult> Intersect(std::shared_ptr<acgm::Ray>& ray) const override;
       
    private:
        const std::string file_name_;
        const glm::mat4 transform_;
        cogs::Mesh mesh_;
    };
}