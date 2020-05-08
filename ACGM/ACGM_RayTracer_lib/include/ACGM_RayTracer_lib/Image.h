#pragma once

#include <string>
#include <glm/glm.hpp>
#include <COGS/Color.h>


namespace acgm
{
    //! Image  - wrapper class for image holding
    class Image
    {
    public:
        //! Image constructor
        explicit Image(const std::string enviro_image_file);
        virtual ~Image() = default;

        //! Color of image pixel
        cogs::Color3f Image::GetColorAt(const glm::vec2 &uv) const;
        //! Free image data from memory
        
    private:
        //! Image path
        const std::string enviro_image_file_;
        uint8_t *img_data_;
        //! Image params
        int height_;
        int width_;
        int bpp_;
    };
}
