#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Resources/Texture.hpp"

#include "Tin/Core/Logger.hpp"

namespace Tin {
	Texture::Texture(const std::string& filename, uint32_t slot) : m_filename(filename), m_id(0), m_slot(slot) {
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filename.c_str(), &m_size.x, &m_size.y, nullptr, 4);

		if (data == nullptr) {
			Logger::Log(Logger::Level::Error, "OpenGL", ("Failed to load texture with filename " + filename + ":\n" + stbi_failure_reason()));
			return;
		}

		// Generate the texture
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Create the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		Logger::Log(Logger::Level::Info, "OpenGL", ("Texture with id " + std::to_string(m_id) + " and filename " + filename + " was successfully created"));

		stbi_image_free(data);
	}

	void Texture::Bind() const {
		glActiveTexture(GL_TEXTURE0 + m_slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::Destroy() const {
		glDeleteTextures(1, &m_id);
	}

	void Texture::TextureUnit(Shader& shader, const std::string& uniform) const {
		shader.SetUniformInt(uniform, m_slot);
	}

	void Texture::ChangeTexture(const std::string& filename) {
		if (m_id == 0) {
			Logger::Log(Logger::Level::Error, "OpenGL", ("Failed to change texture with id " + std::to_string(m_id) + ":\n" + "Original texture was invalid"));
			return;
		}

		stbi_set_flip_vertically_on_load(true);

		int32_t width, height;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, nullptr, 4);

		if (data == nullptr) {
			Logger::Log(Logger::Level::Error, "OpenGL", ("Failed to load texture with filename " + filename + ":\n" + stbi_failure_reason()));
			return;
		}

		glBindTexture(GL_TEXTURE_2D, m_id);
		
		if (m_size.x == width && m_size.y == height) {
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		Logger::Log(Logger::Level::Info, "OpenGL", ("Successfully changed texture with id " + std::to_string(m_id) + " and filename " + m_filename + " to " + filename));

		stbi_image_free(data);

		m_filename = filename;
		m_size = glm::ivec2(width, height);
	}

    std::string Texture::GetFilename() const {
		return m_filename;
	}

	glm::ivec2 Texture::GetSize() const {
		return m_size;
	}

	uint32_t Texture::GetID() const {
		return m_id;
    }
}