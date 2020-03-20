#include <ACGM_RayTracer_lib/Model.h>



acgm::Model::Model(const cogs::Color3f &color)
  : color_(color)
{
}

acgm::Model::Model(const cogs::Color3f& color, cogs::Mesh bunny)
{
    color_ = color;
    this->bunny = bunny;
}

const cogs::Color3f &acgm::Model::Color() const
{
  return color_;
}

cogs::Mesh acgm::Model::GetBunny()
{
    return bunny;
}

// #TODO Implement your functionality here
