#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Renderer.hpp"

#include "Tin/Core/Logger.hpp"

namespace Tin {
    Renderer::Renderer(const Window& window) {
        // Initialize an OpenGL context
        int32_t version = gladLoadGL(glfwGetProcAddress);
        if (version == 0) {
            Logger::Log(Logger::Level::Error, "Tin", "Failed to intialize OpenGL context!");
            glfwTerminate();
            return;
        }
        Logger::Log(Logger::Level::Info, "Tin", "OpenGL context initialized successfully");

        // Set up some OpenGL stuff
        glm::vec2 size = window.GetSize();
        glViewport(0, 0, size.x, size.y);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);

        // Print OpenGL info
		Logger::Log(Logger::Level::Info, "OpenGL", ("OpenGL version: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)))));
		Logger::Log(Logger::Level::Info, "OpenGL", ("GLSL version: " + std::string(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)))));
		Logger::Log(Logger::Level::Info, "OpenGL", ("OpenGL vendor: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR)))));
		Logger::Log(Logger::Level::Info, "OpenGL", ("OpenGL renderer: " + std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER)))));
    }

    void Renderer::Clear() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, ClearColor.a);
    }

    void Renderer::SaveScreenshot(const std::string& filename, const glm::vec2& position, const glm::vec2& size) const {
        int32_t result = SOIL_save_screenshot(filename.c_str(), SOIL_SAVE_TYPE_PNG, position.x, position.y, size.x, size.y);

        if (result == 0) {
			Logger::Log(Logger::Level::Error, "Tin", ("Failed to capture to " + filename + ":\n" + SOIL_last_result()));
		}
		else {
            Logger::Log(Logger::Level::Info, "Tin", ("Successfully saved a capture to " + filename));
		}
    }

    void Renderer::SetViewportSize(const glm::vec2& size) const {
        glViewport(0, 0, size.x, size.y);
    }
}