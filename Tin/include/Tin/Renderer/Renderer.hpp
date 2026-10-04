#ifndef TIN_RENDERER_HPP
#define TIN_RENDERER_HPP

#include "Tin/Core/Window.hpp"
#include "Tin/Core/Logger.hpp"

#include "Tin/Renderer/DataStructures/Color.hpp"
#include "Tin/Renderer/Objects/Skybox.hpp"
#include "Tin/Renderer/Objects/Camera.hpp"
#include "Tin/Renderer/Resources/Shader.hpp"

#include "glm/glm.hpp"

#include <string>

namespace Tin {
    class Renderer {
    public:
        Renderer(const Window& window);

        // Destroys the renderer
        void Destroy();
        // Clears the color, depth and stencil buffers
        void Clear() const;
        // Captures an area and writes it to an image
        void SaveScreenshot(const std::string& filename, const glm::ivec2& position, const glm::ivec2& size) const;

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
        void RenderSkybox(Camera& camera);

    private:
        // Skybox related
        uint32_t m_skyboxVao;
        uint32_t m_skyboxVbo;
        std::unique_ptr<Shader> m_skyboxShader = nullptr;
        std::shared_ptr<Skybox> m_skybox = nullptr;
    };
}

#endif