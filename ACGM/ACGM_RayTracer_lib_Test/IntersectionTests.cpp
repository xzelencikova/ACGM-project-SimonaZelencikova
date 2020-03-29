#include "pch.h"

/*

TEST(IntersectionTests, RayTriangleIntersectionTest)
{
    // Write test for ray-triangle intersections here
    const auto ray = std::make_shared<acgm::Ray>(glm::vec3(0, 0, 0), glm::vec3(0, 0.5, -1), 0.001);
    const auto triangle = std::make_shared<acgm::Triangle>(glm::vec3(0, 0, -1), glm::vec3(1, 0, -1), glm::vec3(0, 2, -1));

    //! u = 0
    EXPECT_TRUE(glm::epsilonEqual<float>(
        -1,
        triangle->Intersect(ray),
        glm::epsilon<float>()
    ));
}

/*
TEST(IntersectionTests, RayPlaneIntersectionTest)
{
  // #TODO: Write test for ray-plane intersections here
    auto ray = std::make_shared<acgm::Ray>(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), 0.001);
    const auto plane_back = std::make_shared<acgm::Plane>(glm::vec3(0, 0, -5), glm::vec3(0, 0, 1), "");

    std::optional<acgm::HitResult> hit;
    hit->ray_param = -1.0f

    EXPECT_TRUE(glm::epsilonEqual<float>(
        hit->ray_param,
        plane_back->Intersect(ray)->ray_param,
        glm::epsilon<float>()
        ));
  //EXPECT_EQ(1, 1);
}*/

/*TEST(IntersectionTests, RaySphereIntersectionTest)
{
    // #TODO: Write test for ray-plane intersections here
    const auto ray = std::make_shared<acgm::Ray>(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), 0.001);
    const auto sphere = std::make_shared<acgm::Sphere>(glm::vec3(0, 0, -5), 5, "");

    std::optional<acgm::HitResult> hit = -1.0f;

    EXPECT_TRUE(glm::epsilonEqual<float>(
        hit->ray_param,
        sphere->Intersect(*ray)->ray_param,
        glm::epsilon<float>();
    ));
    //EXPECT_EQ(1, 1);
}
*/