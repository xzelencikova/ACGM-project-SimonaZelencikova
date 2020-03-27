#include "RayTracerResource.h"
#include "RayTracerGadget.h"
#include <ACGM_RayTracer_lib/SceneImporter.h>
#include <HIRO/HIRO.h>



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
    model_button_->Subscribe([model_selector_](const hiro::gui::Button* button) {
        std::string file_name = model_selector_->GetText();
        ImportAndRender(file_name);
    });
}

void RayTracerGadget::ImportAndRender(std::string fileName)
{
    bool importCheck;
    acgm::SceneImporter SceneImporter;
    acgm::RenderOptions result;
    std::shared_ptr<acgm::Scene> scene;
    importCheck = SceneImporter.Import(fileName);
    result = SceneImporter.GetRenderOptions();
    scene = SceneImporter.GetScene();

    auto resource = std::make_shared<RayTracerResource>("RayTraced Scene");
    //auto resource = std::make_shared<RayTracerResource>("RayTraced Scene", result);
    hiro::AddResource(resource);

    scene->Raytrace(*resource->GetRenderer());
};
