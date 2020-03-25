#pragma once

#include <HIRO/Gadget.h>

#include <HIRO_DRAW/renderers/RasterRenderer.h>



//! Visual part of the RayTracer HIRO module.
class RayTracerGadget
  : public hiro::Gadget
{
public:
  //! Construct with a HIRO resource.
  explicit RayTracerGadget(const hiro::Resource *res);

  void RayTracerGadget::GenerateGui(hiro::GuiGenerator& gui) override;

  void Initialize() override;

private:
  //! Structure specifying how the raster should be rendered.
  hiro::draw::PRasterStyle style_;
};
