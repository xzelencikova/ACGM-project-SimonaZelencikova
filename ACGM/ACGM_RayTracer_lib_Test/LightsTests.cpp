#include "pch.h"



TEST(LightsTests, SunLightIntensityTest)
{
    
    const auto sun_light = std::make_shared<acgm::SunLight>(0.8, glm::vec3(0, 0, -1), glm::vec3(1000.0f, 1000.0f, 1000.0f));
   
    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.8f,
        sun_light->GetIntensityAt(glm::vec3(1.0f, 1.0f, -1.0f)),
        glm::epsilon<float>()
        ));
}

TEST(LightsTests, PointLightIntensityTest)
{
    const auto point_light = std::make_shared<acgm::PointLight>(1, glm::vec3(0, 3, -2), 50, 0, 1);

    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.9976057f,
        point_light->GetIntensityAt(glm::vec3(1.0f, 1.0f, -1.0f)),
        glm::epsilon<float>()
        ));
}

TEST(LightsTests, SpotLightIntensityTest)
{
    const auto spot_light = std::make_shared<acgm::SpotLight>(1, glm::vec3(0, 3, -2), 50, 0, 1, glm::vec3(0, 2, -2), 40, 3);

    //! Angle > Cutoff angle test
    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.0f,
        spot_light->GetIntensityAt(glm::vec3(1.0f, 1.0f, -1.0f)),
        glm::epsilon<float>()
        ));

    //! Angle <= Cutoff angle test
    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.0f,
        spot_light->GetIntensityAt(glm::vec3(-1.0f, 1.0f, 4.0f)),
        glm::epsilon<float>()
        ));

    //EXPECT_EQ(1, 1);
}
