#ifndef TIN_RENDERER_OBJECTS_FRAMEBUFFER_HPP
#define TIN_RENDERER_OBJECTS_FRAMEBUFFER_HPP

#include "glm/glm.hpp"

namespace Tin {
    class Framebuffer {
    public:
        Framebuffer(const glm::vec2& size);

        // Binds the framebuffer
        void Bind() const;
        // Unbinds the framebuffer
        void Unbind() const;
        // Destroys the framebuffer
        void Destroy();

        // Resizes the framebuffer
        void Resize(const glm::vec2& size);

        // Returns the size of the framebuffer
        glm::vec2 GetSize() const;
        // Returns the texture id
        uint32_t GetTextureID() const;
    private:
        uint32_t m_id, m_texture, m_rbo;
        glm::vec2 m_size;
    };
}

#endif