#include "pch.h"



TEST(RefractionTests, RayReflection)
{
    const auto ray = std::make_shared<acgm::Ray>(glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f), 0.001f);

    EXPECT_TRUE(glm::epsilonEqual<float>(
        1.0f,
        ray->GetReflectionDirection(glm::vec3(0, 0, 1)).x,
        glm::epsilon<float>()
        ));

    EXPECT_TRUE(glm::epsilonEqual<float>(
        1.0f,
        ray->GetReflectionDirection(glm::vec3(0, 0, 1)).y,
        glm::epsilon<float>()
        ));

    EXPECT_TRUE(glm::epsilonEqual<float>(
        -1.0f,
        ray->GetReflectionDirection(glm::vec3(0, 0, 1)).z,
        glm::epsilon<float>()
        ));
}

TEST(RefractionTests, RayRefraction)
{
    const auto ray = std::make_shared<acgm::Ray>(glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f), 0.001f);
    glm::vec3 a = ray->GetRefractionDirection(0.5, glm::vec3(0, 0, 1));
    std::cout << a.x << a.y << a.z << std::endl;
    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.5f,
        ray->GetRefractionDirection(0.5, glm::vec3(0, 0, 1)).x,
        glm::epsilon<float>()
        ));

    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.5f,
        ray->GetRefractionDirection(0.5, glm::vec3(0, 0, 1)).y,
        glm::epsilon<float>()
        ));

    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.0f,
        ray->GetRefractionDirection(0.5, glm::vec3(0, 0, 1)).z,
        glm::epsilon<float>()
        ));
}