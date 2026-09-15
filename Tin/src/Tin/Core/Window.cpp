#include "Tin/TinPCH.hpp"
#include "Tin/Core/Window.hpp"

#include "Tin/Core/Logger.hpp"

namespace Tin {
    static void GLFWErrorCallback(int32_t error, const char* description) {
        Logger::Log(Logger::Level::Error, "GLFW", std::string(description));
    }

    Window::Window(const std::string& title, const glm::vec2& size, bool vsync, bool fullscreen) : m_title(title), m_size(size), m_vsync(vsync), m_icon("") {
        // Initialize glfw
        if (!glfwInit()) {
            Logger::Log(Logger::Level::FatalError, "GLFW", "Failed to initialize GLFW!");
            return;
        }
        Logger::Log(Logger::Level::Info, "GLFW", "GLFW initialized successfully");
        glfwSetErrorCallback(GLFWErrorCallback);
        
        glfwDefaultWindowHints();

        // OpenGL context related window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // For fullscreen
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

        m_window = glfwCreateWindow(size.x, size.y, title.c_str(), fullscreen ? monitor : nullptr, nullptr);
        if (!m_window) {
            Logger::Log(Logger::Level::FatalError, "Tin", "Failed to create window!");
            glfwTerminate();
            return;
        }
        Logger::Log(Logger::Level::Info, "Tin", "Window created successfully");

        // Set m_position variable
        int32_t xPos, yPos;
        glfwGetWindowPos(m_window, &xPos, &yPos);
        m_position = glm::vec2(xPos, yPos);

        glfwMakeContextCurrent(m_window);
        glfwSwapInterval(vsync ? 1 : 0);
    }

    void Window::Destroy() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Window::PollEvents() const {
        glfwPollEvents();
    }

    void Window::SwapBuffers() const {
        glfwSwapBuffers(m_window);
    }

    void Window::Update() {
        int32_t width, height, fWidth, fHeight, x, y;
        glfwGetFramebufferSize(m_window, &fWidth, &fHeight);
        glfwGetWindowSize(m_window, &width, &height);
        glfwGetWindowPos(m_window, &x, &y);

        if (m_size.x != width || m_size.y != height) {
            m_size.x = width;
            m_size.y = height;
            glViewport(0, 0, fWidth, fHeight);
        }

        if (m_position.x != x || m_position.y != y) {
            m_position.x = x;
            m_position.y = y;
        }
    }

    bool Window::IsOpen() const {
        return !glfwWindowShouldClose(m_window);
    }

    void Window::SetIcon(const std::string& filename) {
        GLFWimage image[1];
        image[0].pixels = SOIL_load_image(filename.c_str(), &image[0].width, &image[0].height, nullptr, 0);
        glfwSetWindowIcon(m_window, 1, image);
        SOIL_free_image_data(image[0].pixels);
        m_icon = filename;
    }

    void Window::SetVsync(bool vsync) {
        glfwSwapInterval(vsync ? 1 : 0);
        m_vsync = vsync;
    }

    void Window::SetTitle(const std::string& title) {
        glfwSetWindowTitle(m_window, title.c_str());
        m_title = title;
    }

    void Window::SetSize(const glm::vec2& size) {
        glfwSetWindowSize(m_window, size.x, size.y);
        m_size = size;
    }

    void Window::SetPosition(const glm::vec2& position) {
        glfwSetWindowPos(m_window, position.x, position.y);
        m_position = position;
    }

    std::string Window::GetIcon() const {
        return m_icon;
    }

    bool Window::GetVsync() const {
        return m_vsync;
    }

    std::string Window::GetTitle() const {
        return m_title;
    }

    glm::vec2 Window::GetSize() const {
        return m_size;
    }

    glm::vec2 Window::GetPosition() const {
        return m_position;
    }

    double Window::GetTime() const {
        return glfwGetTime();
    }

    GLFWwindow* Window::GetGLFWHandle() const {
        return m_window;
    }
}