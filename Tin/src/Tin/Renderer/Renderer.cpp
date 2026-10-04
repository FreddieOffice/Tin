#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Renderer.hpp"

namespace Tin {
    namespace {
        // Cube vertices for skybox
        const std::vector<float> skyboxVertices = {    
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };

        const std::string skyboxVertShader = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;

            out vec3 TexCoords;

            uniform mat4 CamProjection;
            uniform mat4 CamView;

            void main()
            {
                TexCoords = aPos;
                vec4 pos = CamProjection * CamView * vec4(aPos, 1.0);
                gl_Position = pos.xyww;
            }  
        )";

        const std::string skyboxFragShader = R"(
            #version 330 core
            out vec4 FragColor;

            in vec3 TexCoords;

            uniform samplerCube skybox;

            void main()
            {    
                FragColor = texture(skybox, TexCoords);
            }
        )";
    }

    Renderer::Renderer(const Window& window) {
        // Initialize an OpenGL context
        glfwMakeContextCurrent(window.GetGlfwHandle());
        int32_t version = gladLoadGL(glfwGetProcAddress);
        if (version == 0) {
            Logger::Log(Logger::Level::Error, "Tin", "Failed to create OpenGL context!");
            return;
        }

        Logger::Log(Logger::Level::Info, "Tin", "OpenGL context created successfully");

        // Set up some OpenGL stuff
        glm::ivec2 size = window.GetFramebufferSize();
        glViewport(0, 0, size.x, size.y);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        //glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);

        // Print OpenGL info
		Logger::Log(Logger::Level::Info, "OpenGL", ("OpenGL version: "  + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)))));
		Logger::Log(Logger::Level::Info, "OpenGL", ("GLSL version: "    + std::string(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)))));
		Logger::Log(Logger::Level::Info, "OpenGL", ("OpenGL vendor: "   + std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR)))));
		Logger::Log(Logger::Level::Info, "OpenGL", ("OpenGL renderer: " + std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER)))));
    
        // Create skybox shader
        m_skyboxShader = std::make_unique<Shader>(skyboxVertShader, skyboxFragShader);

        // Create skybox cube mesh
        glGenVertexArrays(1, &m_skyboxVao);
        glGenBuffers(1, &m_skyboxVbo);

        glBindVertexArray(m_skyboxVao);
        glBindBuffer(GL_ARRAY_BUFFER, m_skyboxVbo);

        glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(float), skyboxVertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    }

    void Renderer::Destroy() {
        glDeleteVertexArrays(1, &m_skyboxVao);
        glDeleteBuffers(1, &m_skyboxVbo);
        m_skyboxShader->Destroy();
        m_skybox->Destroy();
    }

    void Renderer::Clear() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SaveScreenshot(const std::string& filename, const glm::ivec2& position, const glm::ivec2& size) const {
        std::vector<unsigned char*> pixelData(size.x * size.y * 3);
        int32_t packAlignment;

        glGetIntegerv(GL_PACK_ALIGNMENT, &packAlignment);
        if (packAlignment != 1) {
            glPixelStorei(GL_PACK_ALIGNMENT, 1);
        }

        // Get the pixel data
        glReadPixels(position.x, position.y, size.x, size.y, GL_RGB, GL_UNSIGNED_BYTE, pixelData.data());

        if (packAlignment != 1) {
            glPixelStorei(GL_PACK_ALIGNMENT, packAlignment);
        }

        // Save the image
        stbi_flip_vertically_on_write(true);
        int32_t result = stbi_write_png(filename.c_str(), size.x, size.y, 3, pixelData.data(), size.x * 3);

        if (result == 0) {
			Logger::Log(Logger::Level::Error, "Tin", ("Failed to capture to " + filename + ":\n" + stbi_failure_reason()));
		} else {
            Logger::Log(Logger::Level::Info, "Tin", ("Successfully saved a capture to " + filename));
		}
    }

    void Renderer::SetClearColor(const Color& clearColor) const {
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    }

    void Renderer::SetViewportSize(const glm::ivec2& size) const {
        glViewport(0, 0, size.x, size.y);
    }

    void Renderer::SetSkybox(std::shared_ptr<Skybox> skybox) {
        m_skybox = skybox;
    }

    std::shared_ptr<Skybox> Renderer::GetSkybox() const {
        return m_skybox;
    }

    void Renderer::RemoveSkybox() {
        if (m_skybox) {
            m_skybox = nullptr;
        }
    }

    void Renderer::RenderSkybox(Camera& camera) {
        if (!m_skybox) { return; }

        glDepthFunc(GL_LEQUAL);

        m_skyboxShader->Use();
        camera.UpdateMatrix(*m_skyboxShader, camera.GetProjectionMatrix(), glm::mat4(glm::mat3(camera.GetViewMatrix()))); // Remove the translation

        // Bind the cubemap
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_skybox->GetCubemapId());

        // Render the skybox cube
        glBindVertexArray(m_skyboxVao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glDepthFunc(GL_LESS);
    }
}