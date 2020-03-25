#include <COGS/Color.h>
#include <glm/glm.hpp>

#include <ACGM_RayTracer_lib/Shader.h>

explicit acgm::Shader::Shader(cogs::Color3f color):color(color)
{
}

cogs::Color3f acgm::Shader::CalculateColor(const ShaderInput& input) const
{
	return color;
}