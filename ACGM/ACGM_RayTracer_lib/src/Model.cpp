#include <ACGM_RayTracer_lib/Model.h>

//! Model constructor
acgm::Model::Model(const std::string name) : name_(name)
{
}

//! Set shader for model
void acgm::Model::SetShader(const std::shared_ptr<acgm::Shader> shader)
{
    shader_ = shader;
}

std::shared_ptr<acgm::Shader> acgm::Model::GetShader() const
{
    return shader_;
}

//! Base intersection of model and ray
std::optional<acgm::HitResult> acgm::Model::Intersect(std::shared_ptr<acgm::Ray>& ray) const
{
    std::optional<acgm::HitResult> result;
    return result;
}