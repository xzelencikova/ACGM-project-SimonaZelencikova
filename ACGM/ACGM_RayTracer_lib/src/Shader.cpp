#include <COGS/Color.h>
#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/Shader.h>

acgm::Shader::Shader(cogs::Color3f color):color(color)
{
}

void acgm::Shader::SetShaders(const std::shared_ptr<acgm::Shader> shader0, const std::shared_ptr<acgm::Shader> shader1)
{
}

cogs::Color3f acgm::Shader::CalculateColor(const ShaderInput& input) const
{
	return color;
}