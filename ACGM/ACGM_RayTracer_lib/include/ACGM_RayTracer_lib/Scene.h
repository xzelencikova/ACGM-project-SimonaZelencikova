#pragma once

#include <vector>
#include <HIRO_DRAW/renderers/RasterRenderer.h>

#include <ACGM_RayTracer_lib/Camera.h>
#include <ACGM_RayTracer_lib/Model.h>
#include <ACGM_RayTracer_lib/Light.h>
#include <ACGM_RayTracer_lib/Shader.h>
#include <ACGM_RayTracer_lib/Image.h>


namespace acgm
{
    //! Scene representation
    class Scene
    {
    public:
        //! Scene constructor
        Scene(const std::shared_ptr<acgm::Camera>& camera, const std::shared_ptr<acgm::Light>& light, const std::vector<std::shared_ptr<acgm::Model>>& models, 
            const glm::vec3 &enviro_up, const glm::vec3& enviro_seam, const float bias, std::string enviro_image_file, const float max_depth);
        ~Scene() = default;

        //! RayTrace the scene
        void Raytrace(hiro::draw::RasterRenderer &renderer) const;
        //! Recursion to calculate glossiness color
        cogs::Color3f ReflectionColor(std::shared_ptr<acgm::Ray> view_ray, ShaderInput input, int index, int max_depth, std::shared_ptr<acgm::Image> image) const;

    private:
        //! Scene camera, light and models
        std::shared_ptr<acgm::Camera> camera;
        std::shared_ptr<acgm::Light> light;
        std::vector<std::shared_ptr<acgm::Model>> models_;
        //! Scene enviro up and seam vectors
        const glm::vec3 enviro_up_;
        const glm::vec3 enviro_seam_;
        const float bias_;
        //! Image file path
        std::string enviro_image_file_;
        int max_depth_;
  };
}
