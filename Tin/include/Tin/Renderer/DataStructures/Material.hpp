#ifndef TIN_RENDERER_DATASTRUCTURES_MATERIAL_HPP
#define TIN_RENDERER_DATASTRUCTURES_MATERIAL_HPP

#include "Tin/Renderer/Resources/Shader.hpp"

#include "Tin/Renderer/DataStructures/Color.hpp"

namespace Tin {
    struct Material {
        Color MatColor;

        // Default constructor
        // Makes a gray colored material
        Material();

        Material(const Color& color);
    };
}

#endif