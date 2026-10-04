#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/DataStructures/Material.hpp"

namespace Tin {
    Material::Material() : colorMap(std::nullopt) {}

    Material::Material(const Color& color, const Texture& colorMap) : color(color), colorMap(colorMap) {}

    bool Material::HasColorMap() const {
        return colorMap.has_value();
    }
}