#pragma once

#include "glm/glm.hpp"

namespace Tin {
    class Framebuffer {
    public:
        explicit Framebuffer(const glm::ivec2& size);

        // Binds the framebuffer
        void Bind() const;
        // Unbinds the framebuffer
        void Unbind() const;
        // Destroys the framebuffer
        void Destroy();

        // Resizes the framebuffer
        void Resize(const glm::ivec2& size);

        // Returns the size of the framebuffer
        [[nodiscard]] glm::ivec2 GetSize() const;
        // Returns the texture ID
        [[nodiscard]] uint32_t GetTextureId() const;
    private:
        uint32_t m_id = 0;
        uint32_t m_textureId = 0;
        uint32_t m_rbo = 0;

        glm::ivec2 m_size;
    };
}
