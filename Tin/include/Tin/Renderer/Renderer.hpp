#ifndef TIN_RENDERER_HPP
#define TIN_RENDERER_HPP

#include "Tin/Renderer/DataStructures/Color.hpp"

#include "Tin/Core/Window.hpp"
#include "Tin/Core/Logger.hpp"

namespace Tin {
    class Renderer {
    public:
        Tin::Color ClearColor;
        Renderer(const Window& window);

        // Clears the color, depth and stencil buffers
        void Clear() const;
    };
}

#endif