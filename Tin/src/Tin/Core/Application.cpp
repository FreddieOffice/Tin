#include "Tin/TinPCH.hpp"
#include "Tin/Core/Application.hpp"

namespace Tin {
    static void GLFWErrorCallback(int32_t error, const char* description) {
        Logger::Log(Logger::Level::Error, "GLFW", std::string(description));
    }

    Application::Application() {
        // Initialize glfw
        if (!glfwInit()) {
            Logger::Log(Logger::Level::Error, "GLFW", "Failed to initialize GLFW!");
            return;
        }

        Logger::Log(Logger::Level::Info, "GLFW", "GLFW initialized successfully");
        glfwSetErrorCallback(GLFWErrorCallback);

        Logger::Log(Logger::Level::Info, "Tin", "Application created successfully");
    }

    Application::~Application() {
        glfwTerminate();
    }

    void Application::PollEvents() const {
        glfwPollEvents();
    }

    double Application::GetTime() const {
        return glfwGetTime();
    }
}
