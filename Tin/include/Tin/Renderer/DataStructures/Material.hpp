#ifndef TIN_RENDERER_DATASTRUCTURES_MATERIAL_HPP
#define TIN_RENDERER_DATASTRUCTURES_MATERIAL_HPP

#include "Tin/Renderer/Resources/Shader.hpp"
#include "Tin/Renderer/Resources/Texture.hpp"

#include "Tin/Renderer/DataStructures/Color.hpp"

#include <string>

namespace Tin {
    struct Material {
        Color color = Color(0.5f, 0.5f, 0.5f);
        std::shared_ptr<Texture> colorMap = nullptr;

        // Default constructor
        // Makes a gray colored material
        Material() = default;

        Material(const Color& color, std::shared_ptr<Texture> colorMap);

        void Bind(Shader& shader) const;
    };
}

#endif
