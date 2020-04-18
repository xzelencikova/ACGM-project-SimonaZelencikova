#include <ACGM_RayTracer_lib/Image.h>

#define STB_IMAGE_IMPLEMENTATION
#include <ACGM_RayTracer_lib/stb_image.h>


acgm::Image::Image(const std::string enviro_image_file):
	enviro_image_file_(enviro_image_file)
{
	if (enviro_image_file_.compare("") != 0)
	{
		img_data_ = stbi_load(enviro_image_file_.c_str(), &width_, &height_, &bpp_, 3);
		printf("Vyska: %dpx, Sirka: %dpx\n", height_, width_);
		printf("Vyska: %d, Sirka: %d\n", int(height_), int(width_));
	}
}

//! Free image
void acgm::Image::FreeImage() const
{
	stbi_image_free(img_data_);
}

//! Color of image pixel
cogs::Color3f acgm::Image::GetColorAt(const glm::vec2& uv) const 
{
	uint8_t pixel_offset = uint8_t(uv.x * int(width_) + int(height_) * uv.y) * 3;
	//printf("%d\n", pixel_offset);
	float r = float(img_data_[pixel_offset]) / 256.0f;
	float g = float(img_data_[pixel_offset + 1]) / 256.0f;
	float b = float(img_data_[pixel_offset + 2]) / 256.0f;
	
	//printf("%d\n", img_data_[pixel_offset]);
	//printf("%f %f %f\n", r, g, b);
	return cogs::Color3f(r, g, b);
}