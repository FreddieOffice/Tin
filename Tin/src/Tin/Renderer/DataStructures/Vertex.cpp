#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/DataStructures/Vertex.hpp"

namespace Tin {
    Vertex::Vertex(glm::vec3 position, glm::vec2 textureUV) : Position(position), TextureUV(textureUV) {}

    bool Vertex::operator==(const Vertex& other) const {
        if (Position == other.Position && TextureUV == other.TextureUV) {
            return true;
        }
        else {
            return false;
        }
    }

    bool Vertex::operator!=(const Vertex& other) const {
        if (Position != other.Position || TextureUV != other.TextureUV) {
            return true;
        }
        else {
            return false;
        }
    }
}