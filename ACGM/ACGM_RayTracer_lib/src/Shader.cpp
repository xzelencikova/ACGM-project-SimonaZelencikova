#include <ACGM_RayTracer_lib/Shader.h>

//! Constructors for shader
acgm::Shader::Shader()
{
}

//! Base CalculateColor returns input color
cogs::Color3f acgm::Shader::CalculateColor(const ShaderInput& input) const
{
	return cogs::Color3f(1.0f, 1.0f, 1.0f);
}
