#include "ACGM_RayTracer_lib/CheckerShader.h"

acgm::CheckerShader::CheckerShader(float cube_size)
{
	this->cube_size = cube_size;
}

float acgm::CheckerShader::GetCubeSize()
{
	return cube_size;
}
