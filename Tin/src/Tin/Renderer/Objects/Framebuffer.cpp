#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Objects/Framebuffer.hpp"

namespace Tin {
    Framebuffer::Framebuffer(const glm::ivec2& size) : m_size(size) {
		// Create the framebuffer
		glGenFramebuffers(1, &m_id);
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);

		// Create the texture
		glGenTextures(1, &m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		// Attach the texture to the framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0);

		// Create the renderbuffer
		glGenRenderbuffers(1, &m_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			Logger::Log(Logger::Level::Error, "Tin", "Failed to create framebuffer: framebuffer incomplete");

			glDeleteFramebuffers(1, &m_id);
			glDeleteTextures(1, &m_textureId);
			glDeleteRenderbuffers(1, &m_rbo);
		} else {
			Logger::Log(Logger::Level::Info, "Tin", "Framebuffer with id " + std::to_string(m_id) + " successfully created");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    void Framebuffer::Bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    }

    void Framebuffer::Unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

	void Framebuffer::Destroy() {
		glDeleteFramebuffers(1, &m_id);
		glDeleteTextures(1, &m_textureId);
		glDeleteRenderbuffers(1, &m_rbo);
	}

    void Framebuffer::Resize(const glm::ivec2& size) {
		if (size.x <= 0 || size.y <= 0) { return; }

		// Resize texture
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		// Resize renderbuffer
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);

        m_size = glm::ivec2(size.x, size.y);
    }

    glm::ivec2 Framebuffer::GetSize() const {
        return m_size;
    }

    uint32_t Framebuffer::GetTextureId() const {
        return m_textureId;
    }
}
