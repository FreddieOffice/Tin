#ifndef TIN_RENDERER_OBJECTS_SKYBOX_HPP
#define TIN_RENDERER_OBJECTS_SKYBOX_HPP

#include "Tin/Renderer/Resources/Shader.hpp"
#include "Tin/Renderer/Objects/Camera.hpp"

#include <string>
#include <vector>
#include <memory>

namespace Tin {
    class Skybox {
    public:
        // Faces must be in this order:
        // +X (right),
        // -X (left),
        // +Y (top),
        // -Y (bottom),
        // +Z (front),
        // -Z (back)
        Skybox(const std::vector<std::string>& faces);

        // Destroys the skybox
        void Destroy();

        // Returns the skyboxes faces
        std::vector<std::string> GetFaces() const;
        // Returns the skybox's cubemap texture id
        uint32_t GetCubemapId() const;
    private:
        uint32_t m_cubemapId;
        std::vector<std::string> m_faces;
    };
}

#endif
