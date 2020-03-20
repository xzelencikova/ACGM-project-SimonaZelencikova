#pragma once

#include <COGS/Color.h>
#include <COGS\Mesh.h>



namespace acgm
{
  //! Model  - abstract base class for scene models
  class Model
  {
  public:
    explicit Model(const cogs::Color3f &color);
    virtual ~Model() = default;

    explicit Model(const cogs::Color3f& color, cogs::Mesh bunny);
    //! Get model color
    const cogs::Color3f &Color() const;
    cogs::Mesh GetBunny();

  private:
    cogs::Color3f color_;
    cogs::Mesh bunny;
  };
}
