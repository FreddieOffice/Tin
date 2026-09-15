#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Resources/Texture.hpp"

#include "Tin/Core/Logger.hpp"

namespace Tin {
	Texture::Texture(const std::string& filename, uint32_t slot) : m_filename(filename), m_slot(slot) {
		glActiveTexture(GL_TEXTURE0 + m_slot);

		m_id = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
        if (m_id == 0) {
            Tin::Logger::Log(Tin::Logger::Level::Error, "OpenGL", ("Failed to load texture with filename " + filename + ":\n" + SOIL_last_result()));
        }
		else {
            Tin::Logger::Log(Tin::Logger::Level::Info, "OpenGL", ("Texture with id " + std::to_string(m_id) + " and filename " + filename + " was successfully created"));
		}

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Bind() const {
		glActiveTexture(GL_TEXTURE0 + m_slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::Destroy() const {
		glDeleteTextures(1, &m_id);
	}

	void Texture::TextureUnit(Tin::Shader& shader, const std::string& uniform) const {
		shader.SetUniformInt(uniform, m_slot);
	}

	void Texture::ChangeTexture(const std::string& filename) {
		m_filename = filename;

		glActiveTexture(GL_TEXTURE0 + m_slot);

		m_id = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		if (m_id == 0) {
			Logger::Log(Logger::Level::Error, "OpenGL", ("Failed to load texture with filename " + filename + ":\n" + SOIL_last_result()));
		}
		else {
            Logger::Log(Logger::Level::Info, "OpenGL", ("Successfully changed texture with id " + std::to_string(m_id) + " and filename " + m_filename + " to " + filename));
		}

		glBindTexture(GL_TEXTURE_2D, 0);

	}

    std::string Texture::GetFilename() const {
		return m_filename;
	}

	uint32_t Texture::GetID() const {
		return m_id;
    }
}