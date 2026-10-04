#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Resources/Texture.hpp"

#include "Tin/Core/Logger.hpp"

namespace Tin {
	Texture::Texture(const std::string& filename, Enum::TextureType type) : m_filename(filename), m_slot(static_cast<uint32_t>(type)) {
		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load(filename.c_str(), &m_size.x, &m_size.y, &m_channels, STBI_default);
		if (!data) {
			Logger::Log(Logger::Level::Error, "Tin", ("Failed to load texture with filename " + filename + ":\n" + stbi_failure_reason()));
			return;
		}

		// Get the image's format for the texture
		int32_t internalFormat;
		int32_t format;

		switch (m_channels) {
		case 4:
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
			break;
		case 3:
			internalFormat = GL_RGB8;
			format = GL_RGB;
			break;
		case 1:
			internalFormat = GL_R8;
			format = GL_RED;
			break;
		}

		// Generate the texture
		glGenTextures(1, &m_Id);
		glBindTexture(GL_TEXTURE_2D, m_Id);

		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Create the texture
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_size.x, m_size.y, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		Logger::Log(Logger::Level::Info, "Tin", ("Texture with id " + std::to_string(m_Id) + " and filename " + filename + " was successfully created"));

		stbi_image_free(data);
	}

	void Texture::Bind() const {
		glActiveTexture(GL_TEXTURE0 + m_slot);
		glBindTexture(GL_TEXTURE_2D, m_Id);
	}

	void Texture::Destroy() const {
		glDeleteTextures(1, &m_Id);
	}

	void Texture::TextureUnit(Shader& shader, const std::string& uniform) const {
		shader.SetUniformInt(uniform, m_slot);
	}

	void Texture::ChangeTexture(const std::string& filename) {
		if (m_Id == 0) {
			Logger::Log(Logger::Level::Error, "Tin", ("Failed to change texture with id " + std::to_string(m_Id) + ":\n" + "Original texture was invalid"));
			return;
		}

		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load(filename.c_str(), &m_size.x, &m_size.y, &m_channels, STBI_default);
		if (!data) {
			Logger::Log(Logger::Level::Error, "Tin", ("Failed to load texture with filename " + filename + ":\n" + stbi_failure_reason()));
			return;
		}

		// Get the image's format for the texture
		int32_t internalFormat;
		int32_t format;

		switch (m_channels) {
		case 4:
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
			break;
		case 3:
			internalFormat = GL_RGB8;
			format = GL_RGB;
			break;
		case 1:
			internalFormat = GL_R8;
			format = GL_RED;
			break;
		}

		glBindTexture(GL_TEXTURE_2D, m_Id);
		
		// Recreate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_size.x, m_size.y, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		Logger::Log(Logger::Level::Info, "Tin", ("Successfully changed texture with id " + std::to_string(m_Id) + " and filename " + m_filename + " to " + filename));

		stbi_image_free(data);

		m_filename = filename;
	}

    std::string Texture::GetFilename() const {
		return m_filename;
	}

	glm::ivec2 Texture::GetSize() const {
		return m_size;
	}

	int32_t Texture::GetChannels() const {
		return m_channels;
	}

	uint32_t Texture::GetId() const {
		return m_Id;
    }
}