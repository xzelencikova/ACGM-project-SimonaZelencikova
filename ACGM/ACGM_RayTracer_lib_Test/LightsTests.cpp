#include "pch.h"
#include <glm/gtc/epsilon.hpp>

#include <ACGM_RayTracer_lib/PointLight.h>
#include <ACGM_RayTracer_lib/SpotLight.h>
#include <ACGM_RayTracer_lib/Light.h>
#include <ACGM_RayTracer_lib/SunLight.h>



TEST(LightsTests, SunLightIntensityTest)
{
    
    const auto sun_light = std::make_shared<acgm::SunLight>(0.8, glm::vec3(0, 0, -1));
   
    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.8f,
        sun_light->GetIntensityAt(glm::vec3(1.0f, 1.0f, -1.0f)),
        glm::epsilon<float>()
        ));

    EXPECT_FALSE(glm::epsilonEqual<float>(
        0.1f,
        sun_light->GetIntensityAt(glm::vec3(1.0f, 1.0f, -1.0f)),
        glm::epsilon<float>()
        ));
  //EXPECT_EQ(1, 1);
}

TEST(LightsTests, PointLightIntensityTest)
{

    const auto point_light = std::make_shared<acgm::PointLight>(1, glm::vec3(0, 3, -2), 50, 0, 1);

    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.9976f,
        point_light->GetIntensityAt(glm::vec3(1.0f, 1.0f, -1.0f)),
        glm::epsilon<float>()
        ));

    EXPECT_FALSE(glm::epsilonEqual<float>(
        0.1f,
        point_light->GetIntensityAt(glm::vec3(1.0f, 1.0f, -1.0f)),
        glm::epsilon<float>()
        ));
    //EXPECT_EQ(1, 1);
}

TEST(LightsTests, SpotLightIntensityTest)
{
    const auto spot_light = std::make_shared<acgm::SpotLight>(1, glm::vec3(0, 3, -2), 50, 0, 1, glm::vec3(-1, -1, -1), 40, 3);

    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.8f,
        spot_light->GetIntensityAt(glm::vec3(1.0f, 1.0f, -1.0f)),
        glm::epsilon<float>()
        ));

    EXPECT_FALSE(glm::epsilonEqual<float>(
        0.1f,
        spot_light->GetIntensityAt(glm::vec3(1.0f, 1.0f, -1.0f)),
        glm::epsilon<float>()
        ));
    //EXPECT_EQ(1, 1);
}
