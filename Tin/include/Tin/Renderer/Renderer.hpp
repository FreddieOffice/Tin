#ifndef TIN_RENDERER_HPP
#define TIN_RENDERER_HPP

#include "Tin/Renderer/DataStructures/Color.hpp"

#include "Tin/Core/Window.hpp"
#include "Tin/Core/Logger.hpp"

#include "glm/glm.hpp"

#include <string>

namespace Tin {
    class Renderer {
    public:
        Color ClearColor;
        Renderer(const Window& window);

        // Clears the color, depth and stencil buffers
        void Clear() const;
        // Captures an area and writes it to an image
        void SaveScreenshot(const std::string& filename, const glm::ivec2& position, const glm::ivec2& size) const;

        // Sets the opengl viewport size
        void SetViewportSize(const glm::ivec2& size) const;
    };
}

#endif