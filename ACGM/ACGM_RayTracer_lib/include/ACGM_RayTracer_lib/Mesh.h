#pragma once

#include <COGS/Mesh.h>
#include <ACGM_RayTracer_lib/Model.h>

namespace acgm
{
    //! Mesh representation
    class Mesh : public Model
    {
    public:
        explicit Mesh(std::string file_name, glm::mat4 transform, std::string name);
        ~Mesh() = default;

        virtual std::optional<acgm::HitResult> Intersect(acgm::Ray & ray) const override;

    private:
        std::string file_name;
        glm::mat4 transform;
        cogs::Mesh mesh_obj;
    };
}