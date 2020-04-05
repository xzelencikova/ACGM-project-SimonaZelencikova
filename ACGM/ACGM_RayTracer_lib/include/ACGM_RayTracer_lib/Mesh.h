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
        //! Mesh constructor
        explicit Mesh(const std::string file_name, const glm::mat4 transform, const std::string name);
        ~Mesh() = default;
        //! Mesh intersection with ray
        virtual std::optional<acgm::HitResult> Intersect(std::shared_ptr<acgm::Ray>& ray) const override;
       
    private:
        //! Mesh file_name
        const std::string file_name_;
        //! Mesh transformation
        const glm::mat4 transform_;
        //! Mesh object
        cogs::Mesh mesh_;
    };
}