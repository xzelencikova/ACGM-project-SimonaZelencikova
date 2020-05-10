#include "pch.h"


TEST(ShaderTests, PhongShaderColorTest)
{

    const auto phong_shader = std::make_shared<acgm::PhongShader>(cogs::Color3f(1.0f, 1.0f, 1.0f), 5, 0.3, 0.7, 0, 0, 0, 0);

    acgm::ShaderInput input;

    input.is_point_in_shadow = true;
    input.light_intensity = 1;
    input.normal = glm::vec3(0, 0, 1);
    input.point = glm::vec3(5, 5, -2);
    input.direction_to_eye = glm::vec3(-5, -5, 2);
    input.direction_to_light = glm::vec3(-5, 4, 2);

    acgm::Color color = phong_shader->CalculateColor(input);

    // ! point in shadow
    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.3f,
        color.color.r,
        glm::epsilon<float>()
        ));

    input.is_point_in_shadow = false;
    color = phong_shader->CalculateColor(input);
    // ! point not in shadow
    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.50869966,
        color.color.r,
        glm::epsilon<float>()
        ));
}

TEST(ShadersTests, CheckerShaderColorTest)
{
    const auto phong_shader_gray = std::make_shared<acgm::PhongShader>(cogs::Color3f(0.1f, 0.1f, 0.1f), 5, 0.3, 0.7, 0, 0, 0, 0);
    const auto phong_shader_white = std::make_shared<acgm::PhongShader>(cogs::Color3f(1.0f, 1.0f, 1.0f), 5, 0.3, 0.7, 0, 0, 0, 0);
    const auto checker_shader = std::make_shared<acgm::CheckerShader>(0.5, phong_shader_white, phong_shader_gray);

    acgm::ShaderInput input;

    input.is_point_in_shadow = true;
    input.light_intensity = 1;
    input.normal = glm::vec3(0, 0, 1);
    input.point = glm::vec3(5, 5, -2);
    input.direction_to_eye = glm::vec3(-5, -5, 2);
    input.direction_to_light = glm::vec3(-5, 4, 2);

    acgm::Color color = checker_shader->CalculateColor(input);
    // ! white point in shadow
    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.3f,
        color.color.r,
        glm::epsilon<float>()
        ));

    input.is_point_in_shadow = false;
    color = checker_shader->CalculateColor(input);

    // ! white point not in shadow
    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.50869966f,
        color.color.r,
        glm::epsilon<float>()
        ));

    input.is_point_in_shadow = true;
    input.light_intensity = 1;
    input.normal = glm::vec3(0, 0, 1);
    input.point = glm::vec3(5.5, 5, -2);
    input.direction_to_eye = glm::vec3(-5.5, -5, 2);
    input.direction_to_light = glm::vec3(-5.5, 4, 2);

    color = checker_shader->CalculateColor(input);
    // ! gray point in shadow
    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.03f,
        color.color.r,
        glm::epsilon<float>()
        ));

    input.is_point_in_shadow = false;
    color = checker_shader->CalculateColor(input);
    // ! gray point not in shadow
    EXPECT_TRUE(glm::epsilonEqual<float>(
        0.04974968f,
        color.color.r,
        glm::epsilon<float>()
        ));
}
