#pragma once
#include <ACGM_RayTracer_lib/Model.h>



namespace acgm
{
    class Sphere : public Model
    {
    public:
    //! Sphere constructor
        explicit Sphere(const glm::vec3 &position, float radius, std::string name);
        virtual ~Sphere() = default;
    
    //! Sphere intersection with ray
        virtual std::optional<HitResult> Intersect(std::shared_ptr<acgm::Ray>& ray) const override;
        const glm::vec3 &GetPosition() const;
        float GetRadius() const;

    private:
        //! Sphere position a radius values
        glm::vec3 position_;
        float radius_;
    };
}
