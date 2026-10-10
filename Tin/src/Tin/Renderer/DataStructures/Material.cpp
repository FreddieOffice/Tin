#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/DataStructures/Material.hpp"

namespace Tin {
    Material::Material(const Color& color, std::shared_ptr<Texture> colorMap) : color(color), colorMap(colorMap) {}

    void Material::Bind(Shader& shader) const {
        shader.SetUniformVec3("Color", glm::vec3(color.r, color.g, color.b));

		// Check if the material has a color map
		if (!colorMap) {
			shader.SetUniformInt("HasColorMap", 0);
		} else {
			shader.SetUniformInt("HasColorMap", 1);
            colorMap->Bind();
	        colorMap->TextureUnit(shader, "ColorMap");
		}
    }
}
