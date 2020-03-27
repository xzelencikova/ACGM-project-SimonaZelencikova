#include <HIRO/HIRO.h>

#include "src/RayTracerResource.h"



int main()
{
  hiro::SetAssetDirectory("../../hiro_libs/assets/");
  hiro::SetIntermediateDirectory("./temp/");

  hiro::Initialize();

  auto resource = std::make_shared<RayTracerResource>("RayTraced Scene");
  hiro::AddResource(resource);

  while (hiro::IsOpen())
  {
    hiro::Update();
  }

  hiro::Terminate();
  return 0;
}
