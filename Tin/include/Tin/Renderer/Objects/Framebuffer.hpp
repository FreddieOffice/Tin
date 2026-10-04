#ifndef TIN_RENDERER_OBJECTS_FRAMEBUFFER_HPP
#define TIN_RENDERER_OBJECTS_FRAMEBUFFER_HPP

#include "glm/glm.hpp"

namespace Tin {
    class Framebuffer {
    public:
        Framebuffer(const glm::ivec2& size);

        // Binds the framebuffer
        void Bind() const;
        // Unbinds the framebuffer
        void Unbind() const;
        // Destroys the framebuffer
        void Destroy();

        // Resizes the framebuffer
        void Resize(const glm::ivec2& size);

        // Returns the size of the framebuffer
        glm::ivec2 GetSize() const;
        // Returns the texture id
        uint32_t GetTextureId() const;
    private:
        uint32_t m_Id = 0;
        uint32_t m_textureId = 0;
        uint32_t m_Rbo = 0;
        
        glm::ivec2 m_size;
    };
}

#endif