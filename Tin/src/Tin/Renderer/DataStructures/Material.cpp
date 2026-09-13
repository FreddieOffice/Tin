#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/DataStructures/Material.hpp"

namespace Tin {
    Material::Material() : MatColor(Color(0.5f, 0.5f, 0.5f)) {}

    Material::Material(const Color& color) : MatColor(color) {}
}