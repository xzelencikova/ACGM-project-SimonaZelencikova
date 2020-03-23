#pragma once
#include <glm/glm.hpp>

namespace acgm
{
    //! Representation of a ray
    class CheckerShader
    {
    public:
        explicit CheckerShader(float cube_size);

        float GetCubeSize();

    private:
        float cube_size;
    };
}