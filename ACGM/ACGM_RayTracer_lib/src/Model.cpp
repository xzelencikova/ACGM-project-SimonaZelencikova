#include <ACGM_RayTracer_lib/Model.h>

acgm::Model::Model(const std::string name)
  : name(name)
{
}

std::string acgm::Model::GetName()
{
    return name;
}

void acgm::Model::SetShader(const std::shared_ptr<acgm::Shader> shader)
{
    this->shader = shader;
}

std::shared_ptr<acgm::Shader> acgm::Model::GetShader() const
{
    return shader;
}

std::optional<acgm::HitResult> acgm::Model::Intersect(std::shared_ptr<acgm::Ray>& ray) const
{
    acgm::HitResult result;
    return result;
}