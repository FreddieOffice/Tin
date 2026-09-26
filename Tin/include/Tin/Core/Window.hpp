#ifndef TIN_CORE_WINDOW_HPP
#define TIN_CORE_WINDOW_HPP

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include <string>

namespace Tin {
    namespace Enum {
        enum class WindowAttribute  {
            VSYNC,
            MAXIMIZED,
            VISIBLE,
            RESIZABLE,
            DECORATED,
            FLOATING,
        };
    }

    struct WindowConfig {
        std::string title, icon = "";
        glm::ivec2 size, position = glm::ivec2(-1, -1);

        bool vsync = false, maximized = false, visible = true,
        resizable = true, decorated = true, floating = false;
    };

    class Window {
    public:
        // Setting size.x or size.y to a negative number will make the window be as big as the screen on that axis
        // Setting position.x or position.y to a negative number will center the window on that axis
        Window(const WindowConfig& config);

        // Destroys the window
        void Destroy();
        // Swaps the front and back buffers
        void SwapBuffers() const;
        // Updates the window size and window position
        void Update();
        // Checks if the window is open
        bool IsOpen() const;
        // Closes the window
        void Close() const;

        // Sets an attribute of the window (e.g. vsync, fullscreen, etc)
        void SetAttribute(Enum::WindowAttribute attribute, bool value);
        // Sets the window icon
        // To remove the icon, filename should be ""
        void SetIcon(const std::string& filename);
        // Sets the window title
        void SetTitle(const std::string& title);
        // Sets the window size
        void SetSize(const glm::ivec2& size);
        // Sets the window position
        void SetPosition(const glm::ivec2& position);

        // Returns the attribute's value
        bool GetAttribute(Enum::WindowAttribute attribute) const;
        // Returns the icon file name
        std::string GetIcon() const;
        // Returns the window title
        std::string GetTitle() const;
        // Returns the window size
        glm::ivec2 GetSize() const;
        // Returns the window's framebuffer size
        glm::ivec2 GetFramebufferSize() const;
        // Returns the window position
        glm::ivec2 GetPosition() const;

        // Returns the GLFW window handle
        GLFWwindow* GetGLFWHandle() const;
    private:
        GLFWwindow* m_GLFWHandle = nullptr;

        // GLFW does not provide a getter for vsync and icon
        std::string m_title, m_icon;
        glm::ivec2 m_size, m_framebufferSize, m_position;
        bool m_vsync;
    };
}

#endif