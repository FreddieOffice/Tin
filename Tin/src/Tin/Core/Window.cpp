#include "Tin/TinPCH.hpp"
#include "Tin/Core/Window.hpp"

#include "Tin/Core/Logger.hpp"

namespace Tin {
    static void GLFWErrorCallback(int32_t error, const char* description) {
        Logger::Log(Logger::Level::Error, "GLFW", std::string(description));
    }

    Window::Window(const WindowConfig& config) : m_config(config) {
        // Initialize glfw
        if (!glfwInit()) {
            Logger::Log(Logger::Level::Error, "GLFW", "Failed to initialize GLFW!");
            return;
        }
        Logger::Log(Logger::Level::Info, "GLFW", "GLFW initialized successfully");
        glfwSetErrorCallback(GLFWErrorCallback);
        
        glfwDefaultWindowHints();

        // OpenGL context related window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Fullscreen
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

        if (config.fullscreen == true) {
            glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);
            m_config.size = glm::vec2(videoMode->width, videoMode->height);
        }

        // Size
        if (config.size.x < 0) {
            m_config.size.x = videoMode->width;
        }
        if (config.size.y < 0) {
            m_config.size.y = videoMode->height;
        }

        // Position
        if (config.position.x < 0) {
            m_config.position.x = (videoMode->width - m_config.size.x) / 2;
        }
        if (config.position.y < 0) {
            m_config.position.y = (videoMode->height - m_config.size.y) / 2;
        }

        // Window related hints
        glfwWindowHint(GLFW_MAXIMIZED, config.maximized);
        glfwWindowHint(GLFW_RESIZABLE, config.resizable);
        glfwWindowHint(GLFW_DECORATED, config.decorated);
        glfwWindowHint(GLFW_FLOATING, config.floating);

        glfwWindowHint(GLFW_POSITION_X, m_config.position.x);
        glfwWindowHint(GLFW_POSITION_Y, m_config.position.y);

        glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);

        m_GLFWHandle = glfwCreateWindow(m_config.size.x, m_config.size.y, config.title.c_str(), nullptr, nullptr);
        if (!m_GLFWHandle) {
            Logger::Log(Logger::Level::Error, "Tin", "Failed to create window!");
            return;
        }
        Logger::Log(Logger::Level::Info, "Tin", "Window created successfully");

        // Set icon
        if (config.icon != "") {
            GLFWimage image[1];
            image[0].pixels = SOIL_load_image(config.icon.c_str(), &image[0].width, &image[0].height, nullptr, 0);
            glfwSetWindowIcon(m_GLFWHandle, 1, image);
            SOIL_free_image_data(image[0].pixels);
        }

        m_config.icon = config.icon;

        glfwMakeContextCurrent(m_GLFWHandle);
        glfwSwapInterval(config.vsync ? 1 : 0);
    }

    void Window::Destroy() {
        glfwDestroyWindow(m_GLFWHandle);
        glfwTerminate();
    }

    void Window::PollEvents() const {
        glfwPollEvents();
    }

    void Window::SwapBuffers() const {
        glfwSwapBuffers(m_GLFWHandle);
    }

    void Window::Update() {
        int32_t width, height, x, y;
        glfwGetWindowSize(m_GLFWHandle, &width, &height);
        glfwGetWindowPos(m_GLFWHandle, &x, &y);

        if (m_config.size.x != width || m_config.size.y != height) {
            m_config.size = glm::vec2(width, height);
        }

        if (m_config.position.x != x || m_config.position.y != y) {
            m_config.position = glm::vec2(x, y);
        }
    }

    bool Window::IsOpen() const {
        return !glfwWindowShouldClose(m_GLFWHandle);
    }

    void Window::Close() const {
        glfwSetWindowShouldClose(m_GLFWHandle, 1);
    }

    void Window::SetSetting(Enum::WindowSetting setting, bool value) {
        switch (setting) {
        case Enum::WindowSetting::VSYNC:
            glfwMakeContextCurrent(m_GLFWHandle);
            glfwSwapInterval(value ? 1 : 0);
            m_config.vsync = value;
            break;
        case Enum::WindowSetting::FULLSCREEN:
            if (value == true) {
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

                m_windowedSize = m_config.size;
                m_windowedPosition = m_config.position;

                glfwSetWindowAttrib(m_GLFWHandle, GLFW_DECORATED, GLFW_FALSE);
                glfwSetWindowMonitor(m_GLFWHandle, nullptr, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);
                m_config.size = glm::vec2(videoMode->width, videoMode->height);
                m_config.position = glm::vec2(0, 0);
            }
            else {
                glfwSetWindowAttrib(m_GLFWHandle, GLFW_DECORATED, GLFW_TRUE);
                glfwSetWindowMonitor(m_GLFWHandle, nullptr, m_windowedPosition.x, m_windowedPosition.y, m_windowedSize.x, m_windowedSize.y, 0);
                m_config.size = m_windowedSize;
                m_config.position = m_windowedPosition;
            }

            m_config.decorated = value;
            m_config.fullscreen = value;
            break;
        case Enum::WindowSetting::MAXIMIZED:
            if (value == true) {
                glfwMaximizeWindow(m_GLFWHandle);
            }
            else {
                glfwRestoreWindow(m_GLFWHandle);
            }

            m_config.maximized = value;
            break;
        case Enum::WindowSetting::RESIZABLE:
            glfwSetWindowAttrib(m_GLFWHandle, GLFW_RESIZABLE, value);
            m_config.resizable = value;
            break;
        case Enum::WindowSetting::DECORATED:
            glfwSetWindowAttrib(m_GLFWHandle, GLFW_DECORATED, value);
            m_config.decorated = value;
            break;
        case Enum::WindowSetting::FLOATING:
            glfwSetWindowAttrib(m_GLFWHandle, GLFW_FLOATING, value);
            m_config.floating = value;
            break;
        }
    }

    void Window::SetIcon(const std::string& filename) {
        if (filename == "") {
            glfwSetWindowIcon(m_GLFWHandle, 0, nullptr);
        }
        else {
            GLFWimage image[1];
            image[0].pixels = SOIL_load_image(filename.c_str(), &image[0].width, &image[0].height, nullptr, 0);
            glfwSetWindowIcon(m_GLFWHandle, 1, image);
            SOIL_free_image_data(image[0].pixels);
        }

        m_config.icon = filename;
    }

    void Window::SetTitle(const std::string& title) {
        glfwSetWindowTitle(m_GLFWHandle, title.c_str());
        m_config.title = title;
    }

    void Window::SetSize(const glm::vec2& size) {
        glfwSetWindowSize(m_GLFWHandle, size.x, size.y);
        m_config.size = size;
    }

    void Window::SetPosition(const glm::vec2& position) {
        glfwSetWindowPos(m_GLFWHandle, position.x, position.y);
        m_config.position = position;
    }

    bool Window::GetSetting(Enum::WindowSetting setting) const {
        switch (setting) {
        case Enum::WindowSetting::VSYNC:
            return m_config.vsync;
            break;
        case Enum::WindowSetting::FULLSCREEN:
            return m_config.fullscreen;
            break;
        case Enum::WindowSetting::MAXIMIZED:
            return m_config.maximized;
            break;
        case Enum::WindowSetting::RESIZABLE:
            return m_config.resizable;
            break;
        case Enum::WindowSetting::DECORATED:
            return m_config.decorated;
            break;
        case Enum::WindowSetting::FLOATING:
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

    glm::vec2 Window::GetSize() const {
        return m_config.size;
    }

    glm::vec2 Window::GetPosition() const {
        return m_config.position;
    }

    double Window::GetTime() const {
        return glfwGetTime();
    }

    GLFWwindow* Window::GetGLFWHandle() const {
        return m_GLFWHandle;
    }
}