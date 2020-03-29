#pragma once
#include <Utils/Dialogs.h>

//#include <glm/glm.hpp>
#include <ACGM_RayTracer_lib/Ray.h>


namespace acgm
{
    //! Representation of a triangle in mesh object
    class Triangle
    {
    public:
        explicit Triangle(const glm::vec3 vertex_x, const glm::vec3 vertex_y, const glm::vec3 vertex_z);
        virtual ~Triangle() = default;

        glm::vec3 GetVertexX() const;
        glm::vec3 GetVertexY() const;
        glm::vec3 GetVertexZ() const;

        float Intersect(std::shared_ptr<acgm::Ray> ray) const;

    private:
        const glm::vec3 vertex_x_;
        const glm::vec3 vertex_y_;
        const glm::vec3 vertex_z_;
    };
}
