#ifndef TIN_RENDERER_HPP
#define TIN_RENDERER_HPP

#include "Tin/Core/Window.hpp"
#include "Tin/Core/Logger.hpp"

#include "Tin/Renderer/DataStructures/Color.hpp"
#include "Tin/Renderer/DataStructures/Material.hpp"
#include "Tin/Renderer/DataStructures/Transform.hpp"

#include "Tin/Renderer/Objects/Camera.hpp"
#include "Tin/Renderer/Objects/Mesh.hpp"
#include "Tin/Renderer/Objects/Skybox.hpp"

#include "Tin/Renderer/Resources/Shader.hpp"

#include "glm/glm.hpp"

#include <string>

namespace Tin {
    struct RenderPacket {
        Mesh* mesh;
        Material* material;
        glm::mat4 transform;
        Shader* shader;
    };

    class Renderer {
    public:
        Renderer(const Window& window);

        // Destroys the renderer
        void Destroy();
        // Clears the color, depth and stencil buffers
        void Clear() const;
        // Captures an area and writes it to an image
        void SaveScreenshot(const std::string& filename, const glm::ivec2& position, const glm::ivec2& size) const;

        // Set view projection
        void BeginScene(const Camera& camera);
        // Submit geometry
        void Submit(Mesh& mesh, Material& material, const glm::mat4& transform, Shader& shader);
        // Render everything
        void EndScene();

        // Sets the clear color
        void SetClearColor(const Color& clearColor) const;
        // Sets the opengl viewport size
        void SetViewportSize(const glm::ivec2& size) const;

        // Sets the skybox
        void SetSkybox(std::shared_ptr<Skybox> skybox);
        // Returns the skybox
        std::shared_ptr<Skybox> GetSkybox() const;
        // Removes the skybox
        void RemoveSkybox();
        // Renders the skybox
        void RenderSkybox();

        uint32_t GetDrawCalls() const;
        uint32_t GetTriangleCount() const;
    private:
        // Render queue
        std::vector<RenderPacket> m_commandQueue;
        glm::mat4 m_projectionMatrix{};
        glm::mat4 m_viewMatrix{};
        uint32_t m_drawCalls = 0;
        uint32_t m_triangles = 0;

        // Skybox related
        uint32_t m_skyboxVao = 0;
        uint32_t m_skyboxVbo = 0;
        std::unique_ptr<Shader> m_skyboxShader = nullptr;
        std::shared_ptr<Skybox> m_skybox = nullptr;
    };
}

#endif
