#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/DataStructures/Material.hpp"

namespace Tin {
    Material::Material() : color(Color(0.5f, 0.5f, 0.5f)), colorMap(std::nullopt) {}

    Material::Material(const Color& color, const std::string& colorMapFilename) : color(color) {
        colorMap = Texture(colorMapFilename, 0);
    }

    bool Material::HasColorMap() const {
        return colorMap.has_value();
    }
}