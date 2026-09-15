#ifndef TIN_CORE_WINDOW_HPP
#define TIN_CORE_WINDOW_HPP

#include <string>

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

namespace Tin {
    class Window {
    public:
        Window(const std::string& title, const glm::vec2& size, bool vsync = false, bool fullscreen = false);

        // Destroys the window
        void Destroy();
        // Processes all pending events
        void PollEvents() const;
        // Swaps the front and back buffers
        void SwapBuffers() const;
        // Updates the OpenGL viewport size, window size and window position
        void Update();
        // Checks if the window is open
        bool IsOpen() const;

        // Sets the window icon
        // To remove the icon, filepath should be ""
        void SetIcon(const std::string& filename);
        // Sets vsync
        void SetVsync(bool vsync);
        // Sets the window title
        void SetTitle(const std::string& title);
        // Sets the window size
        void SetSize(const glm::vec2& size);
        // Sets the window position
        void SetPosition(const glm::vec2& position);

        // Returns the icon file name
        std::string GetIcon() const;
        // Returns vsync
        bool GetVsync() const;
        // Returns the window title
        std::string GetTitle() const;
        // Returns the window size
        glm::vec2 GetSize() const;
        // Returns the window position
        glm::vec2 GetPosition() const;
        // Returns time since initialization
        double GetTime() const;

        // Returns the GLFW window handle
        GLFWwindow* GetGLFWHandle() const;
    private:
        GLFWwindow* m_window = nullptr;

        std::string m_title, m_icon;
        bool m_vsync;
        glm::vec2 m_size, m_position;
    };
}

#endif