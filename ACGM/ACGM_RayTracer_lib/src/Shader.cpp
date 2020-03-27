#include <COGS/Color.h>
#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/Shader.h>

acgm::Shader::Shader(cogs::Color3f color):color(color)
{
}

acgm::Shader::Shader()
{
}

cogs::Color3f acgm::Shader::CalculateColor(const ShaderInput& input) const
{
	return color;
}