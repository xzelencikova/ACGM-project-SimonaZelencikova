#include <ACGM_RayTracer_lib/Ray.h>

#include "RayTracerGadget.h"
#include "RayTracerResource.h"
#include <ACGM_RayTracer_lib/SceneImporter.h>




RayTracerResource::RayTracerResource(const std::string &name)
  : hiro::Resource(hiro::ResourceId(name, "RayTracerResource"))
{
  raster_renderer_ = std::make_shared<hiro::draw::RasterRenderer>();

  //acgm::RenderOptions render_opt;
  //raster_renderer_->SetResolution({ 512, 512 });//render_opt.resolution.x, render_opt.resolution.y });
}

hiro::PGadget RayTracerResource::CreateGadget()
{
  return std::make_shared<RayTracerGadget>(this);
}

hiro::draw::PRasterRenderer RayTracerResource::GetRenderer() const
{
  return raster_renderer_;
}
