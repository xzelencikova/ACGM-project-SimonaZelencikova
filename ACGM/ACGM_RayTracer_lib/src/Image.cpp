#include <ACGM_RayTracer_lib/Image.h>

#define STB_IMAGE_IMPLEMENTATION
#include <ACGM_RayTracer_lib/stb_image.h>
#include <iostream>


acgm::Image::Image(const std::string enviro_image_file):
	enviro_image_file_(enviro_image_file)
{
	if (enviro_image_file_.compare("") != 0)
	{
		img_data_ = stbi_load(enviro_image_file_.c_str(), &width_, &height_, &bpp_, 3);
	}
}

//! Color of image pixel
cogs::Color3f acgm::Image::GetColorAt(const glm::vec2& uv) const 
{
	uint32_t x = uint32_t(uv.x * width_) % width_;
	uint32_t y = uint32_t(uv.y * height_) % height_;
	uint32_t pixel_offset = (y * width_ + x) * 3;
	
	float r = float(img_data_[pixel_offset]) / 255.0f;
	float g = float(img_data_[pixel_offset + 1]) / 255.0f;
	float b = float(img_data_[pixel_offset + 2]) / 255.0f;
	
	return cogs::Color3f(r, g, b);
}