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
    std::optional<glm::vec3> a = ray->GetRefractionDirection(0.5, 1, glm::vec3(0, 0, 1));
    
    if (a)
    {
        glm::vec3 result = glm::vec3(a->x, a->y, a->z);
        EXPECT_TRUE(glm::epsilonEqual<float>(
            2.0f,
            result.x,
            glm::epsilon<float>()
            ));

        EXPECT_TRUE(glm::epsilonEqual<float>(
            2.0f,
            result.y,
            glm::epsilon<float>()
            ));

        EXPECT_TRUE(glm::epsilonEqual<float>(
            1.0f,
            result.z,
            glm::epsilon<float>()
            ));
    }
}