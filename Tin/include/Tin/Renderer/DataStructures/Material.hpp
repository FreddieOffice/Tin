#ifndef TIN_RENDERER_DATASTRUCTURES_MATERIAL_HPP
#define TIN_RENDERER_DATASTRUCTURES_MATERIAL_HPP

#include "Tin/Renderer/Resources/Shader.hpp"
#include "Tin/Renderer/Resources/Texture.hpp"

#include "Tin/Renderer/DataStructures/Color.hpp"

#include <string>
#include <optional>

namespace Tin {
    struct Material {
        Color color;
        std::optional<Texture> colorMap;

        // Default constructor
        // Makes a gray colored material
        Material();

        Material(const Color& color, const std::string& colorMapFilename = ""); 
        
        // Checks if the material has a color map
        bool HasColorMap() const;
    };

}

#endif