#pragma once
#include <Utils/Dialogs.h>

#include <glm/glm.hpp>
#include <ACGM_RayTracer_lib/Ray.h>


namespace acgm
{
    //! Representation of a triangle in mesh object
    class Triangle
    {
    public:
        explicit Triangle(const glm::vec3 vertexX, const glm::vec3 vertexY, const glm::vec3 vertexZ);
        virtual ~Triangle() = default;

        float Intersect(std::shared_ptr<acgm::Ray> ray) const;

    private:
        glm::vec3 vertexX;
        glm::vec3 vertexY;
        glm::vec3 vertexZ;
    };
}
