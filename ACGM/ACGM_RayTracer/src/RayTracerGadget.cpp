#include "RayTracerResource.h"
#include "RayTracerGadget.h"



RayTracerGadget::RayTracerGadget(const hiro::Resource *res)
  : hiro::Gadget(res)
{
}

void RayTracerGadget::Initialize()
{
  hiro::Gadget::Initialize();
  style_ = std::make_shared<hiro::draw::RasterStyle>();
  style_->use_nearest_filtering = true;
  AddRenderer(GetResource<RayTracerResource>()->GetRenderer(), style_);
}

void RayTracerGadget::GenerateGui(hiro::GuiGenerator& gui)
{
    hiro::Gadget::GenerateGui(gui);
    hiro::gui::Droplist* model_selector_;
    hiro::gui::Button* model_button_;
    model_selector_ = gui.AddDroplist("Scene File")
        ->AddItemsIndexed({ "scene0.txt", "scene1.txt", "scene2.txt" })
        ->Set(0);

    model_button_ = gui.AddButton("Import and Render");
}