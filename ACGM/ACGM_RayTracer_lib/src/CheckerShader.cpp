#include "ACGM_RayTracer_lib/CheckerShader.h"

acgm::CheckerShader::CheckerShader(float cube_size, const std::shared_ptr<Shader> shader0, const std::shared_ptr<Shader> shader1):
	cube_size(cube_size), shader0(shader0), shader1(shader1)
{
}

float acgm::CheckerShader::GetCubeSize()
{
	return cube_size;
}

cogs::Color3f acgm::CheckerShader::CalculateColor(const ShaderInput& input) const
{
	float bias = 0.001;
	int choose_shader = floor(input.point.x / cube_size + bias) + floor(input.point.y / cube_size + bias) + floor(input.point.z / cube_size + bias);
	
	if (choose_shader % 2 == 0)
		return shader0->CalculateColor(input);
	else return shader1->CalculateColor(input);
}
