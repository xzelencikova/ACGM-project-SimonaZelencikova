#include <HIRO/HIRO.h>
//! #TODO Use cogs::Mesh to import your mesh models.
#include <COGS/Mesh.h>

#include "src/RayTracerResource.h"



int main()
{
  hiro::SetAssetDirectory("../../hiro_libs/assets/");
  hiro::SetIntermediateDirectory("./temp/");

  hiro::Initialize();

  auto resource = std::make_shared<RayTracerResource>("RayTraced Scene");
  hiro::AddResource(resource);

  // The Scene to be rendered
  // #TODO Initialize this scene with a single camera and multiple models
  const acgm::Scene scene;

  cogs::Mesh bunny;
  bunny.Import("3d-models/bunny.fbx");

  cogs::Transform transform;
  transform.SetRotation(glm::quat(1.0, 0.2f, 0.5f, 0.2f));
  printf("%f %f %f %f", transform.GetRotation().w, transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z);
  transform.SetPosition(glm::vec3(0, 0, -4.5f));
  bunny.points->Transform(transform);

  acgm::Model bunny_obj = acgm::Model(cogs::Color3f(0.9f, 1.0f, 0.0f), bunny);

  // RayTrace the scene. Draw onto the raster renderer.
  scene.Raytrace(*resource->GetRenderer(), bunny_obj);

  while (hiro::IsOpen())
  {
    hiro::Update();
  }

  hiro::Terminate();
  return 0;
}
