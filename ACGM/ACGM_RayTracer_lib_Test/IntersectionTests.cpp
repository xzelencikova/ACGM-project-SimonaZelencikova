#include "pch.h"
#include <glm/gtc/epsilon.hpp>

#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/Plane.h>
#include <ACGM_RayTracer_lib/Sphere.h>
#include <ACGM_RayTracer_lib/Mesh.h>


TEST(IntersectionTests, RayPlaneIntersectionTest)
{
  // #TODO: Write test for ray-plane intersections here
    auto ray = std::make_shared<acgm::Ray>(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1));
    const auto plane_back = std::make_shared<acgm::Plane>(glm::vec3(0, 0, 5), glm::vec3(0, 0, 1));

    std::optional<acgm::HitResult> hit;

    EXPECT_TRUE(glm::epsilonEqual<float>(
        hit->ray_param,
        plane_back->Intersect(ray)->ray_param,
        glm::epsilon<float>()
        ));
  //EXPECT_EQ(1, 1);
}

/*TEST(IntersectionTests, RaySphereIntersectionTest)
{
    // #TODO: Write test for ray-plane intersections here
    const auto ray = std::make_shared<acgm::Ray>(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1));
    const auto sphere = std::make_shared<acgm::Sphere>(glm::vec3(0, 0, 5), glm::vec3(0, 0, 1));

    std::optional<acgm::HitResult> hit;

    EXPECT_TRUE(glm::epsilonEqual<float>(
        hit->ray_param,
        sphere->Intersect(*ray)->ray_param,
        glm::epsilon<float>();
    ));
    //EXPECT_EQ(1, 1);
}

TEST(IntersectionTests, RayMeshIntersectionTest)
{
    // #TODO: Write test for ray-plane intersections here
    const auto ray = std::make_shared<acgm::Ray>();
    const auto mesh = std::make_shared<acgm::Mesh>();

    std::optional<acgm::HitResult> hit;

    EXPECT_TRUE(glm::epsilonEqual<float>(
        hit->ray_param,
        plane_back->Intersect(ray)->ray_param,
        glm::epsilon<float>();
    ));
    //EXPECT_EQ(1, 1);
}
*/