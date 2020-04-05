#pragma once
#include <Utils/Dialogs.h>

#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/Model.h>


namespace acgm
{
    //! Representation of a triangle in mesh object
    class Triangle
    {
    public:
        //! Triangle constructor
        explicit Triangle(const glm::vec3 vertex_x, const glm::vec3 vertex_y, const glm::vec3 vertex_z);
        virtual ~Triangle() = default;

        //! Triangle vertexes getters methods
        glm::vec3 GetVertexX() const;
        glm::vec3 GetVertexY() const;
        glm::vec3 GetVertexZ() const;

        //! Triangle intersection with ray
        std::optional<acgm::HitResult> Intersect(std::shared_ptr<acgm::Ray> ray) const;

    private:
        //! Triangle vertexes x,y,z
        const glm::vec3 vertex_x_;
        const glm::vec3 vertex_y_;
        const glm::vec3 vertex_z_;
    };
}
