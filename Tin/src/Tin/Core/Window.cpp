#include "Tin/TinPCH.hpp"
#include "Tin/Core/Window.hpp"

#include "Tin/Core/Context.hpp"
#include "Tin/Core/Logger.hpp"

namespace Tin {
    Window::Window(const WindowConfig& config) : m_title(config.title), m_icon(config.icon), m_size(config.size), m_position(config.position), m_vsync(config.vsync) {
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

        m_GlfwHandle = glfwCreateWindow(m_size.x, m_size.y, config.title.c_str(), nullptr, nullptr);
        if (!m_GlfwHandle) {
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
                glfwSetWindowIcon(m_GlfwHandle, 1, image);
            }

            stbi_image_free(image[0].pixels);
        }

        // Set framebuffer size
        glfwGetFramebufferSize(m_GlfwHandle, &m_framebufferSize.x, &m_framebufferSize.y);

        glfwMakeContextCurrent(m_GlfwHandle);
        glfwSwapInterval(config.vsync ? 1 : 0);
        glfwPollEvents();
    }

    void Window::Destroy() {
        glfwDestroyWindow(m_GlfwHandle);
    }

    void Window::SwapBuffers() const {
        glfwSwapBuffers(m_GlfwHandle);
    }

    void Window::Update() {
        glm::ivec2 size, framebufferSize, position;
        glfwGetWindowSize(m_GlfwHandle, &size.x, &size.y);
        glfwGetFramebufferSize(m_GlfwHandle, &framebufferSize.x, &framebufferSize.y);
        glfwGetWindowPos(m_GlfwHandle, &position.x, &position.y);

        if (m_size.x != size.x || m_size.y != size.y) {
            m_size = size;
            m_framebufferSize = framebufferSize;
        }

        if (m_position.x != position.x || m_position.y != position.y) {
            m_position = position;
        }
    }

    bool Window::IsOpen() const {
        return !glfwWindowShouldClose(m_GlfwHandle);
    }

    void Window::Close() const {
        glfwSetWindowShouldClose(m_GlfwHandle, 1);
    }

    void Window::SetAttribute(Enum::WindowAttribute attribute, bool value) {
        switch (attribute) {
        case Enum::WindowAttribute::Vsync:
            glfwMakeContextCurrent(m_GlfwHandle);
            glfwSwapInterval(value ? 1 : 0);
            m_vsync = value;
            break;
        case Enum::WindowAttribute::Maximized:
            if (value) {
                glfwMaximizeWindow(m_GlfwHandle);
            } else {
                glfwRestoreWindow(m_GlfwHandle);
            }

            break;
        case Enum::WindowAttribute::Visible:
            if (value) {
                glfwShowWindow(m_GlfwHandle);
            } else {
                glfwHideWindow(m_GlfwHandle);
            }

            break;
        case Enum::WindowAttribute::Resizable:
            glfwSetWindowAttrib(m_GlfwHandle, GLFW_RESIZABLE, value);
            break;
        case Enum::WindowAttribute::Decorated:
            glfwSetWindowAttrib(m_GlfwHandle, GLFW_DECORATED, value);
            break;
        case Enum::WindowAttribute::Floating:
            glfwSetWindowAttrib(m_GlfwHandle, GLFW_FLOATING, value);
            break;
        }
    }

    void Window::SetIcon(const std::string& filename) {
        if (filename.empty()) {
            glfwSetWindowIcon(m_GlfwHandle, 0, nullptr);
        } else {
            GLFWimage image[1];

            stbi_set_flip_vertically_on_load(false);
            image[0].pixels = stbi_load(filename.c_str(), &image[0].width, &image[0].height, nullptr, STBI_rgb_alpha);

            if (!image[0].pixels) {
                Logger::Log(Logger::Level::Error, "Tin", "Failed to load icon with filename " + filename + ":\n" + stbi_failure_reason());
            } else {
                glfwSetWindowIcon(m_GlfwHandle, 1, image);
            }
            
            stbi_image_free(image[0].pixels);
        }

        m_icon = filename;
    }

    void Window::SetTitle(const std::string& title) {
        glfwSetWindowTitle(m_GlfwHandle, title.c_str());
        m_title = title;
    }

    void Window::SetSize(const glm::ivec2& size) {
        glfwSetWindowSize(m_GlfwHandle, size.x, size.y);
        m_size = size;
    }

    void Window::SetPosition(const glm::ivec2& position) {
        glfwSetWindowPos(m_GlfwHandle, position.x, position.y);
        m_position = position;
    }

    bool Window::GetAttribute(Enum::WindowAttribute attribute) const {
        switch (attribute) {
        case Enum::WindowAttribute::Vsync:
            return m_vsync;
            break;
        case Enum::WindowAttribute::Maximized:
            return glfwGetWindowAttrib(m_GlfwHandle, GLFW_MAXIMIZED);
            break;
        case Enum::WindowAttribute::Visible:
            return glfwGetWindowAttrib(m_GlfwHandle, GLFW_VISIBLE);
            break;
        case Enum::WindowAttribute::Resizable:
            return glfwGetWindowAttrib(m_GlfwHandle, GLFW_RESIZABLE);
            break;
        case Enum::WindowAttribute::Decorated:
            return glfwGetWindowAttrib(m_GlfwHandle, GLFW_DECORATED);
            break;
        case Enum::WindowAttribute::Floating:
            return glfwGetWindowAttrib(m_GlfwHandle, GLFW_FLOATING);
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

    GLFWwindow* Window::GetGlfwHandle() const {
        return m_GlfwHandle;
    }
}