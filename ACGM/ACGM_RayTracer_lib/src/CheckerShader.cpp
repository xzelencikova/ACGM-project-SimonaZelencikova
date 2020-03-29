#include "ACGM_RayTracer_lib/CheckerShader.h"


//! Checker Shader constructor
acgm::CheckerShader::CheckerShader(const float cube_size, const std::shared_ptr<Shader> shader0, const std::shared_ptr<Shader> shader1):
	cube_size_(cube_size), shader0_(shader0), shader1_(shader1)
{
}

//! Calculate color for checker shader
cogs::Color3f acgm::CheckerShader::CalculateColor(const ShaderInput& input) const
{
	float bias = 0.001;
	int32_t choose_shader = floor((input.point.x / cube_size_) + bias) + floor((input.point.y / cube_size_) + bias) + floor((input.point.z / cube_size_) + bias);
	
	//! Decision, which cube will be rendered
	if (choose_shader % 2 == 0)
	{
		return shader0_->CalculateColor(input);
	}
	else
	{
		return shader1_->CalculateColor(input);
	}
}
