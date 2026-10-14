#include "Tin/TinPCH.hpp"
#include "Tin/Core/Window.hpp"

namespace Tin {
    Window::Window(const WindowConfig& config) : m_config(config) {
        glfwDefaultWindowHints();

        // OpenGL context related window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Get the video mode
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

        // Configure size
        // If either coordinate is below 0, set the window size to monitor size on that axis
        if (config.size.x < 0) {
            m_config.size.x = videoMode->width;
        }
        if (config.size.y < 0) {
            m_config.size.y = videoMode->height;
        }

        // Configure position
        // If either coordinate is below 0, center the window on that axis
        if (config.position.x < 0) {
            m_config.position.x = static_cast<int32_t>((videoMode->width - m_config.size.x) / 2);
        }
        if (config.position.y < 0) {
            m_config.position.y = static_cast<int32_t>((videoMode->height - m_config.size.y) / 2);
        }

        // Window related hints
        glfwWindowHint(GLFW_VISIBLE, config.visible);
        glfwWindowHint(GLFW_MAXIMIZED, config.maximized);
        glfwWindowHint(GLFW_RESIZABLE, config.resizable);
        glfwWindowHint(GLFW_DECORATED, config.decorated);
        glfwWindowHint(GLFW_FLOATING, config.floating);

        glfwWindowHint(GLFW_POSITION_X, m_config.position.x);
        glfwWindowHint(GLFW_POSITION_Y, m_config.position.y);

        m_glfwHandle = glfwCreateWindow(m_config.size.x, m_config.size.y, config.title.c_str(), nullptr, nullptr);
        if (!m_glfwHandle) {
            Logger::Log(Logger::Level::Error, "Tin", "Failed to create window!");
            return;
        }

        Logger::Log(Logger::Level::Info, "Tin", "Window created successfully");

        // Set icon
        if (!config.icon.empty()) {
            GLFWimage image[1];

            stbi_set_flip_vertically_on_load(false); // Just in case
            image[0].pixels = stbi_load(config.icon.c_str(), &image[0].width, &image[0].height, nullptr, STBI_rgb_alpha);

            if (!image[0].pixels) {
                Logger::Log(Logger::Level::Error, "Tin", "Failed to load icon with filename " + config.icon + ":\n" + stbi_failure_reason());
            } else {
                glfwSetWindowIcon(m_glfwHandle, 1, image);
            }

            stbi_image_free(image[0].pixels);
        }

        glfwMakeContextCurrent(m_glfwHandle);
        glfwSwapInterval(config.vsync ? 1 : 0);
        glfwPollEvents();

        // Create an OpenGL context
        int32_t version = gladLoadGL(glfwGetProcAddress);
        if (version == 0) {
            Logger::Log(Logger::Level::Error, "Tin", "Failed to create OpenGL context!");
            return;
        }

        Logger::Log(Logger::Level::Info, "Tin", "OpenGL context created successfully");

        // Print OpenGL info
		Logger::Log(Logger::Level::Info, "OpenGL", ("OpenGL version: "  + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)))));
		Logger::Log(Logger::Level::Info, "OpenGL", ("GLSL version: "    + std::string(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)))));
		Logger::Log(Logger::Level::Info, "OpenGL", ("OpenGL vendor: "   + std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR)))));
		Logger::Log(Logger::Level::Info, "OpenGL", ("OpenGL renderer: " + std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER)))));

        // Set framebuffer size and glViewport
        glfwGetFramebufferSize(m_glfwHandle, &m_framebufferSize.x, &m_framebufferSize.y);
        glViewport(0, 0, m_framebufferSize.x, m_framebufferSize.y);
    }

    void Window::Destroy() {
        glfwDestroyWindow(m_glfwHandle);
    }

    void Window::SwapBuffers() const {
        glfwSwapBuffers(m_glfwHandle);
    }

    void Window::Update() {
        glm::ivec2 size;
        glm::ivec2 framebufferSize;
        glm::ivec2 position;

        glfwGetWindowSize(m_glfwHandle, &size.x, &size.y);
        glfwGetFramebufferSize(m_glfwHandle, &framebufferSize.x, &framebufferSize.y);
        glfwGetWindowPos(m_glfwHandle, &position.x, &position.y);

        if (m_config.size.x != size.x || m_config.size.y != size.y) {
            m_config.size = size;
            m_framebufferSize = framebufferSize;
        }

        if (m_config.position.x != position.x || m_config.position.y != position.y) {
            m_config.position = position;
        }
    }

    bool Window::IsOpen() const {
        return !glfwWindowShouldClose(m_glfwHandle);
    }

    void Window::Close() const {
        glfwSetWindowShouldClose(m_glfwHandle, 1);
    }

    void Window::SetAttribute(WindowAttribute attribute, bool value) {
        switch (attribute) {
        case WindowAttribute::Vsync:
            glfwMakeContextCurrent(m_glfwHandle);
            glfwSwapInterval(value ? 1 : 0);
            m_config.vsync = value;
            break;
        case WindowAttribute::Maximized:
            if (value) {
                glfwMaximizeWindow(m_glfwHandle);
            } else {
                glfwRestoreWindow(m_glfwHandle);
            }

            m_config.maximized = value;

            break;
        case WindowAttribute::Visible:
            if (value) {
                glfwShowWindow(m_glfwHandle);
            } else {
                glfwHideWindow(m_glfwHandle);
            }

            m_config.visible = value;

            break;
        case WindowAttribute::Resizable:
            glfwSetWindowAttrib(m_glfwHandle, GLFW_RESIZABLE, value);
            m_config.resizable = value;
            break;
        case WindowAttribute::Decorated:
            glfwSetWindowAttrib(m_glfwHandle, GLFW_DECORATED, value);
            m_config.decorated = value;
            break;
        case WindowAttribute::Floating:
            glfwSetWindowAttrib(m_glfwHandle, GLFW_FLOATING, value);
            m_config.floating = value;
            break;
        }
    }

    void Window::SetIcon(const std::string& filename) {
        if (filename.empty()) {
            glfwSetWindowIcon(m_glfwHandle, 0, nullptr);
        } else {
            GLFWimage image[1];

            stbi_set_flip_vertically_on_load(false);
            image[0].pixels = stbi_load(filename.c_str(), &image[0].width, &image[0].height, nullptr, STBI_rgb_alpha);

            if (!image[0].pixels) {
                Logger::Log(Logger::Level::Error, "Tin", "Failed to load icon with filename " + filename + ":\n" + stbi_failure_reason());
            } else {
                glfwSetWindowIcon(m_glfwHandle, 1, image);
            }

            stbi_image_free(image[0].pixels);
        }

        m_config.icon = filename;
    }

    void Window::SetTitle(const std::string& title) {
        glfwSetWindowTitle(m_glfwHandle, title.c_str());
        m_config.title = title;
    }

    void Window::SetSize(const glm::ivec2& size) {
        glfwSetWindowSize(m_glfwHandle, size.x, size.y);
        m_config.size = size;
    }

    void Window::SetPosition(const glm::ivec2& position) {
        glfwSetWindowPos(m_glfwHandle, position.x, position.y);
        m_config.position = position;
    }

    bool Window::GetAttribute(WindowAttribute attribute) const {
        switch (attribute) {
        case WindowAttribute::Vsync:
            return m_config.vsync;
            break;
        case WindowAttribute::Maximized:
            return m_config.maximized;
            break;
        case WindowAttribute::Visible:
            return m_config.visible;
            break;
        case WindowAttribute::Resizable:
            return m_config.resizable;
            break;
        case WindowAttribute::Decorated:
            return m_config.decorated;
            break;
        case WindowAttribute::Floating:
            return m_config.floating;
            break;
        }
    }

    std::string Window::GetIcon() const {
        return m_config.icon;
    }

    std::string Window::GetTitle() const {
        return m_config.title;
    }

    glm::ivec2 Window::GetSize() const {
        return m_config.size;
    }

    glm::ivec2 Window::GetFramebufferSize() const {
        return m_framebufferSize;
    }

    glm::ivec2 Window::GetPosition() const {
        return m_config.position;
    }

    GLFWwindow* Window::GetGlfwHandle() const {
        return m_glfwHandle;
    }
}
