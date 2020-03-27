#include "ACGM_RayTracer_lib/CheckerShader.h"

acgm::CheckerShader::CheckerShader(float cube_size):
	cube_size(cube_size)
{
}

float acgm::CheckerShader::GetCubeSize()
{
	return cube_size;
}

void acgm::CheckerShader::SetShaders(const std::shared_ptr<acgm::Shader> shader0, const std::shared_ptr<acgm::Shader> shader1)
{
	this->shader0 = std::make_shared<acgm::Shader>(shader0);
	this->shader1 = std::make_shared<acgm::Shader>(shader1);
}

cogs::Color3f acgm::CheckerShader::CalculateColor(const ShaderInput& input) const
{
	float bias = 0.001;
	int choose_shader = floor(input.point.x / cube_size + bias) + floor(input.point.y / cube_size + bias) + floor(input.point.z / cube_size + bias);
	
	if (choose_shader % 2 == 0)
		return shader0->CalculateColor(input);
	else return shader1->CalculateColor(input);
}
