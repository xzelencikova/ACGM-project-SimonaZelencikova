#include "pch.h"


//! BLACK COLOR
TEST(ImageTest, FirstColorPixelTest)
{
    const auto image = std::make_shared<acgm::Image>("dummy.jpg");
    cogs::Color3f color = image->GetColorAt(glm::vec2(0.0, 0.0));

    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.0f,
        color.r,
        glm::epsilon<float>()
        ));

    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.0f,
        color.g,
        glm::epsilon<float>()
        ));

    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.0f,
        color.b, 
        glm::epsilon<float>()
        ));
}

//! PURPLE COLOR
TEST(ImageTest, SecondColorPixelTest)
{
    const auto image = std::make_shared<acgm::Image>("dummy.jpg");
    cogs::Color3f color = image->GetColorAt(glm::vec2(0.5, 0.5));

    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.17254902f,
        color.r,
        glm::epsilon<float>()
        ));

    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.10588235f,
        color.g,
        glm::epsilon<float>()
        ));

    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.12941177f,
        color.b,
        glm::epsilon<float>()
        ));
}