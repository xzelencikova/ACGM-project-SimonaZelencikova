#include "pch.h"


//TEST(ShaderTests, PhongShaderColorTest)
//{
//
//    const auto phong_shader = std::make_shared<acgm::PhongShader>(cogs::Color3f(1.0f, 1.0f, 1.0f), 5, 0.3, 0.7, 0);
//
//    acgm::ShaderInput input;
//
//    input.is_point_in_shadow = true;
//    input.light_intensity = 1;
//    input.normal = glm::vec3(0, 0, 1);
//    input.point = glm::vec3(5, 5, -2);
//    input.direction_to_eye = glm::vec3(-5, -5, 2);
//    input.direction_to_light = glm::vec3(-5, 4, 2);
//
//    // ! point in shadow
//    EXPECT_TRUE(glm::epsilonEqual<float>(
//        cogs::Color3f(0.027f, 0.027f, 0.027f).r,
//        phong_shader->CalculateColor(input).r,
//        glm::epsilon<float>()
//        ));
//    
//    input.is_point_in_shadow = false;
//    // ! point not in shadow
//    EXPECT_TRUE(glm::epsilonEqual<float>(
//        cogs::Color3f(0.208698f, 0.208698f, 0.208698f).r,
//        phong_shader->CalculateColor(input).r,
//        glm::epsilon<float>()
//        ));
//
//    //EXPECT_EQ(1, 1);
//}

//TEST(ShadersTests, CheckerShaderColorTest)
//{
//    const auto phong_shader_gray = std::make_shared<acgm::PhongShader>(cogs::Color3f(0.1f, 0.1f, 0.1f), 5, 0.3, 0.7, 0);
//    const auto phong_shader_white = std::make_shared<acgm::PhongShader>(cogs::Color3f(1.0f, 1.0f, 1.0f), 5, 0.3, 0.7, 0);
//    const auto checker_shader = std::make_shared<acgm::CheckerShader>(0.5, phong_shader_white, phong_shader_gray);
//
//    acgm::ShaderInput input;
//
//    input.is_point_in_shadow = true;
//    input.light_intensity = 1;
//    input.normal = glm::vec3(0, 0, 1);
//    input.point = glm::vec3(5, 5, -2);
//    input.direction_to_eye = glm::vec3(-5, -5, 2);
//    input.direction_to_light = glm::vec3(-5, 4, 2);
//
//    // ! white point in shadow
//    EXPECT_TRUE(glm::epsilonEqual<float>(
//        cogs::Color3f(0.027f, 0.027f, 0.027f).r,
//        checker_shader->CalculateColor(input).r,
//        glm::epsilon<float>()
//        ));
//
//    input.is_point_in_shadow = false;
//    // ! white point not in shadow
//    EXPECT_TRUE(glm::epsilonEqual<float>(
//        cogs::Color3f(0.208698f, 0.208698f, 0.208698f).r,
//        checker_shader->CalculateColor(input).r,
//        glm::epsilon<float>()
//        ));
//
//    input.is_point_in_shadow = true;
//    input.light_intensity = 1;
//    input.normal = glm::vec3(0, 0, 1);
//    input.point = glm::vec3(5.5, 5, -2);
//    input.direction_to_eye = glm::vec3(-5.5, -5, 2);
//    input.direction_to_light = glm::vec3(-5.5, 4, 2);
//
//    // ! gray point in shadow
//    EXPECT_TRUE(glm::epsilonEqual<float>(
//        cogs::Color3f(0.0081f, 0.0081f, 0.0081f).r,
//        checker_shader->CalculateColor(input).r,
//        glm::epsilon<float>()
//        ));
//
//    input.is_point_in_shadow = false;
//    // ! gray point not in shadow
//    EXPECT_TRUE(glm::epsilonEqual<float>(
//        cogs::Color3f(0.019005f, 0.019005f, 0.019005f).r,
//        checker_shader->CalculateColor(input).r,
//        glm::epsilon<float>()
//        ));
//}
