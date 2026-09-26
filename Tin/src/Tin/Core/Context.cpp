#include "Tin/TinPCH.hpp"
#include "Tin/Core/Context.hpp"

#include "Tin/Core/Logger.hpp"

namespace Tin{
    static void GLFWErrorCallback(int32_t error, const char* description) {
        Logger::Log(Logger::Level::Error, "GLFW", std::string(description));
    }

    Context& Context::GetInstance() {
        static Context instance;
        return instance;
    }

    void Context::Init() {
        // Check if context was already initialized
        if (m_isInitialized) {
            Logger::Log(Logger::Level::Warning, "Tin", "Context already initialized!");
            return;
        }

        // Initialize glfw
        if (!glfwInit()) {
            Logger::Log(Logger::Level::Error, "GLFW", "Failed to initialize GLFW!");
            return;
        }

        Logger::Log(Logger::Level::Info, "GLFW", "GLFW initialized successfully");
        glfwSetErrorCallback(GLFWErrorCallback);

        m_isInitialized = true;

        Logger::Log(Logger::Level::Info, "Tin", "Context initialized successfully");
    }

    void Context::Destroy() {
        glfwTerminate();
    }

    void Context::PollEvents() const {
        glfwPollEvents();
    }

    double Context::GetTime() const {
        return glfwGetTime();
    }
}