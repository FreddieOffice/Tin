#include "Tin/TinPCH.hpp"
#include "Tin/Core/Window.hpp"

#include "Tin/Core/Context.hpp"
#include "Tin/Core/Logger.hpp"

namespace Tin {
    Window::Window(const WindowConfig& config) : m_title(config.title), m_size(config.size), m_position(config.position), m_vsync(config.vsync) {
        glfwDefaultWindowHints();

        // OpenGL context related window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Get the video mode
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

        // Size
        if (config.size.x < 0) {
            m_size.x = videoMode->width;
        }
        if (config.size.y < 0) {
            m_size.y = videoMode->height;
        }

        // Position
        if (config.position.x < 0) {
            m_position.x = static_cast<int32_t>((videoMode->width - m_size.x) / 2);
        }
        if (config.position.y < 0) {
            m_position.y = static_cast<int32_t>((videoMode->height - m_size.y) / 2);
        }

        // Window related hints
        glfwWindowHint(GLFW_VISIBLE, config.visible);
        glfwWindowHint(GLFW_MAXIMIZED, config.maximized);
        glfwWindowHint(GLFW_RESIZABLE, config.resizable);
        glfwWindowHint(GLFW_DECORATED, config.decorated);
        glfwWindowHint(GLFW_FLOATING, config.floating);

        glfwWindowHint(GLFW_POSITION_X, m_position.x);
        glfwWindowHint(GLFW_POSITION_Y, m_position.y);

        m_GLFWHandle = glfwCreateWindow(m_size.x, m_size.y, config.title.c_str(), nullptr, nullptr);
        if (!m_GLFWHandle) {
            Logger::Log(Logger::Level::Error, "Tin", "Failed to create window!");
            return;
        }
        Logger::Log(Logger::Level::Info, "Tin", "Window created successfully");

        // Set framebuffer size
        glfwGetFramebufferSize(m_GLFWHandle, &m_framebufferSize.x, &m_framebufferSize.y);

        // Set icon
        if (!config.icon.empty()) {
            GLFWimage image[1];

            stbi_set_flip_vertically_on_load(false); // Just in case
            image[0].pixels = stbi_load(config.icon.c_str(), &image[0].width, &image[0].height, nullptr, 4);

            if (image[0].pixels == nullptr) {
                Logger::Log(Logger::Level::Error, "Tin", "Failed to load icon with filename " + config.icon + ":\n" + stbi_failure_reason());
            }
            else {
                glfwSetWindowIcon(m_GLFWHandle, 1, image);
            }

            stbi_image_free(image[0].pixels);
        }

        m_icon = config.icon;

        glfwMakeContextCurrent(m_GLFWHandle);
        glfwSwapInterval(config.vsync ? 1 : 0);
    }

    void Window::Destroy() {
        glfwDestroyWindow(m_GLFWHandle);
    }

    void Window::SwapBuffers() const {
        glfwSwapBuffers(m_GLFWHandle);
    }

    void Window::Update() {
        glm::ivec2 size, framebufferSize, position;
        glfwGetWindowSize(m_GLFWHandle, &size.x, &size.y);
        glfwGetFramebufferSize(m_GLFWHandle, &framebufferSize.x, &framebufferSize.y);
        glfwGetWindowPos(m_GLFWHandle, &position.x, &position.y);

        if (m_size.x != size.x || m_size.y != size.y) {
            m_size = size;
            m_framebufferSize = framebufferSize;
        }

        if (m_position.x != position.x || m_position.y != position.y) {
            m_position = position;
        }
    }

    bool Window::IsOpen() const {
        return !glfwWindowShouldClose(m_GLFWHandle);
    }

    void Window::Close() const {
        glfwSetWindowShouldClose(m_GLFWHandle, 1);
    }

    void Window::SetAttribute(Enum::WindowAttribute attribute, bool value) {
        switch (attribute) {
        case Enum::WindowAttribute::VSYNC:
            glfwMakeContextCurrent(m_GLFWHandle);
            glfwSwapInterval(value ? 1 : 0);
            m_vsync = value;
            break;
        case Enum::WindowAttribute::MAXIMIZED:
            if (value) {
                glfwMaximizeWindow(m_GLFWHandle);
            }
            else {
                glfwRestoreWindow(m_GLFWHandle);
            }

            break;
        case Enum::WindowAttribute::VISIBLE:
            if (value) {
                glfwShowWindow(m_GLFWHandle);
            }
            else {
                glfwHideWindow(m_GLFWHandle);
            }

            break;
        case Enum::WindowAttribute::RESIZABLE:
            glfwSetWindowAttrib(m_GLFWHandle, GLFW_RESIZABLE, value);
            break;
        case Enum::WindowAttribute::DECORATED:
            glfwSetWindowAttrib(m_GLFWHandle, GLFW_DECORATED, value);
            break;
        case Enum::WindowAttribute::FLOATING:
            glfwSetWindowAttrib(m_GLFWHandle, GLFW_FLOATING, value);
            break;
        }
    }

    void Window::SetIcon(const std::string& filename) {
        if (filename.empty()) {
            glfwSetWindowIcon(m_GLFWHandle, 0, nullptr);
        }
        else {
            GLFWimage image[1];

            stbi_set_flip_vertically_on_load(false);
            image[0].pixels = stbi_load(filename.c_str(), &image[0].width, &image[0].height, nullptr, 4);

            if (image[0].pixels == nullptr) {
                Logger::Log(Logger::Level::Error, "Tin", "Failed to load icon with filename " + filename + ":\n" + stbi_failure_reason());
            }
            else {
                glfwSetWindowIcon(m_GLFWHandle, 1, image);
            }
            
            stbi_image_free(image[0].pixels);
        }

        m_icon = filename;
    }

    void Window::SetTitle(const std::string& title) {
        glfwSetWindowTitle(m_GLFWHandle, title.c_str());
        m_title = title;
    }

    void Window::SetSize(const glm::ivec2& size) {
        glfwSetWindowSize(m_GLFWHandle, size.x, size.y);
        m_size = size;
    }

    void Window::SetPosition(const glm::ivec2& position) {
        glfwSetWindowPos(m_GLFWHandle, position.x, position.y);
        m_position = position;
    }

    bool Window::GetAttribute(Enum::WindowAttribute attribute) const {
        switch (attribute) {
        case Enum::WindowAttribute::VSYNC:
            return m_vsync;
            break;
        case Enum::WindowAttribute::MAXIMIZED:
            return glfwGetWindowAttrib(m_GLFWHandle, GLFW_MAXIMIZED);
            break;
        case Enum::WindowAttribute::VISIBLE:
            return glfwGetWindowAttrib(m_GLFWHandle, GLFW_VISIBLE);
            break;
        case Enum::WindowAttribute::RESIZABLE:
            return glfwGetWindowAttrib(m_GLFWHandle, GLFW_RESIZABLE);
            break;
        case Enum::WindowAttribute::DECORATED:
            return glfwGetWindowAttrib(m_GLFWHandle, GLFW_DECORATED);
            break;
        case Enum::WindowAttribute::FLOATING:
            return glfwGetWindowAttrib(m_GLFWHandle, GLFW_FLOATING);
            break;
        }
    }

    std::string Window::GetIcon() const {
        return m_icon;
    }

    std::string Window::GetTitle() const {
        return m_title;
    }

    glm::ivec2 Window::GetSize() const {
        return m_size;
    }

    glm::ivec2 Window::GetFramebufferSize() const {
        return m_framebufferSize;
    }

    glm::ivec2 Window::GetPosition() const {
        return m_position;
    }

    GLFWwindow* Window::GetGLFWHandle() const {
        return m_GLFWHandle;
    }
}