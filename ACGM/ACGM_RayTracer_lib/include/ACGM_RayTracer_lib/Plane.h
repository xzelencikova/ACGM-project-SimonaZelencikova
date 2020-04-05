#pragma once

#include <ACGM_RayTracer_lib/Model.h>



namespace acgm
{
  //! Plane representation
    class Plane : public Model
    {
    public:
        //! Plane constructor
        explicit Plane(const glm::vec3 point, const glm::vec3 normal, const std::string name);
        virtual ~Plane() = default;

        //! Plane intersection with ray
        virtual std::optional<acgm::HitResult> Intersect(std::shared_ptr<acgm::Ray>& ray) const override;

    private:
        //! Plane point and normal vectors
        glm::vec3 point_;
        glm::vec3 normal_;
    };
}
