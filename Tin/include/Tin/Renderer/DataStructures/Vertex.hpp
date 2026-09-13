#ifndef TIN_RENDERER_DATASTRUCTURES_VERTEX_HPP
#define TIN_RENDERER_DATASTRUCTURES_VERTEX_HPP

#include "glm/glm.hpp"

namespace Tin {
    struct Vertex {
        glm::vec3 Position;
        glm::vec2 TextureUV;

        Vertex(glm::vec3 position, glm::vec2 textureUV);

        bool operator==(const Vertex& other) const;
        bool operator!=(const Vertex& other) const;
    };
}

#endif