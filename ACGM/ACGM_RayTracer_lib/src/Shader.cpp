#include <ACGM_RayTracer_lib/Shader.h>

//! Constructors for shader
acgm::Shader::Shader()
{
}

acgm::Shader::Shader(const cogs::Color3f color):color_(color)
{
}

//! Base CalculateColor returns input color
cogs::Color3f acgm::Shader::CalculateColor(const ShaderInput& input) const
{
	return color_;
}