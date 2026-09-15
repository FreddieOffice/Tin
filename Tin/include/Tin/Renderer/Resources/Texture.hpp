#ifndef TIN_RENDERER_RESOURCES_TEXTURE_HPP
#define TIN_RENDERER_RESOURCES_TEXTURE_HPP

#include <string>

#include "Tin/Renderer/Resources/Shader.hpp"

#include "glm/glm.hpp"

namespace Tin {
	class Texture {
	public:
		Texture(const std::string& filename, uint32_t slot);

		// Binds the texture
		void Bind() const;
		// Destroys the texture
		void Destroy() const;

		// Assigns a texture unit to a texture uniform
		void TextureUnit(Shader& shader, const std::string& uniform) const;

		// Changes the texture to a new one
		void ChangeTexture(const std::string& filename);

		// Returns the filename of the texture
		std::string GetFilename() const;
		// Returns the texture id
		uint32_t GetID() const;
	private:
		std::string m_filename;

		uint32_t m_id;
		uint32_t m_slot;
	};
}

#endif