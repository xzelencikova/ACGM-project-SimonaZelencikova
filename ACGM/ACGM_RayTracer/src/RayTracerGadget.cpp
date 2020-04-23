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
    hiro::gui::NumericInt* model_reflection_depth_;

    model_selector_ = gui.AddDroplist("Scene File")
        ->AddItemsIndexed({ "scene0.txt", "scene1.txt", "scene2.txt", "scene3.txt", "scene4.txt", "scene5.txt", "scene6.txt" })
        ->Set(0);
    model_reflection_depth_ = gui.AddNumericInt("Max reflection depth")
        ->Set(10)
        ->SetMax(10)
        ->SetMin(0);
    model_button_ = gui.AddButton("Import and Render");
    model_button_->Subscribe([model_selector_, model_reflection_depth_](const hiro::gui::Button* button) {
        std::string file_name = model_selector_->GetText();
        int reflection_depth = model_reflection_depth_->Get();
        ImportAndRenderScene(file_name, reflection_depth);
    });
}

void RayTracerGadget::ImportAndRenderScene(std::string fileName, int depth)
{
    bool importCheck;
    acgm::SceneImporter scene_importer;
    acgm::RenderOptions render_opt;
    std::shared_ptr<acgm::Scene> scene;
    
    importCheck = scene_importer.Import(fileName);
    render_opt = scene_importer.GetRenderOptions();
    scene = scene_importer.GetScene();

    //! Set resolution
    auto resource = std::make_shared<RayTracerResource>("RayTraced Scene");
    resource->GetRenderer()->SetResolution({ render_opt.resolution.x, render_opt.resolution.y });
   
    hiro::AddResource(resource);
    printf("%d\n", depth);

    scene->Raytrace(*resource->GetRenderer());
};
