#ifndef TIN_RENDERER_RESOURCES_TEXTURE_HPP
#define TIN_RENDERER_RESOURCES_TEXTURE_HPP

#include "Tin/Renderer/Resources/Shader.hpp"

#include "glm/glm.hpp"

#include <string>

namespace Tin {
	namespace Enum {
		enum class TextureType {
			ColorMap
		};
	}

	class Texture {
	public:
		Texture(const std::string& filename, Enum::TextureType type);

		// Binds the texture
		void Bind() const;
		// Destroys  the texture
		void Destroy() const;

		// Assigns a texture unit to a texture uniform
		void TextureUnit(Shader& shader, const std::string& uniform) const;

		// Changes the texture to a different one
		void ChangeTexture(const std::string& filename);

		// Returns the filename of the texture
		std::string GetFilename() const;
		// Returns the size of the texture
		glm::ivec2 GetSize() const;
		// Returns the textures channels
		int32_t GetChannels() const;
		// Returns the texture id
		uint32_t GetId() const;
	private:
		std::string m_filename;
		glm::ivec2 m_size;
		int32_t m_channels;

		uint32_t m_Id = 0;
		uint32_t m_slot;
	};
}

#endif