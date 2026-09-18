#include "Tin/TinPCH.hpp"
#include "Tin/Core/InputHandler.hpp"

namespace Tin {
    InputHandler::InputHandler(const Window& window) : m_handle(window.GetGLFWHandle()) {}

    bool InputHandler::IsKeyPressed(Enum::Key key) const {
        return (glfwGetKey(m_handle, static_cast<uint32_t>(key)) == GLFW_PRESS);
    }

    bool InputHandler::IsMouseButtonPressed(Enum::MouseButton button) const {
        return (glfwGetMouseButton(m_handle, static_cast<uint32_t>(button)) == GLFW_PRESS);
    }

    bool InputHandler::IsKeyReleased(Enum::Key key) const {
        return (glfwGetKey(m_handle, static_cast<uint32_t>(key)) == GLFW_RELEASE);
    }

    bool InputHandler::IsMouseButtonReleased(Enum::MouseButton button) const {
        return (glfwGetMouseButton(m_handle, static_cast<uint32_t>(button)) == GLFW_RELEASE);
    }

    void InputHandler::SetCursorState(Enum::CursorState state) {
        switch (state) {
        case Enum::CursorState::NORMAL:
            glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;
        case Enum::CursorState::HIDDEN:
            glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            break;
        case Enum::CursorState::DISABLED:
            glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        case Enum::CursorState::CONFINED:
            glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
            break;
        }

        m_cursorState = state;
    }

    void InputHandler::SetCursorPosition(glm::vec2 position) const {
        glfwSetCursorPos(m_handle, position.x, position.y);
    }

    Enum::CursorState InputHandler::GetCursorState() const {
        return m_cursorState;
    }

    glm::vec2 InputHandler::GetCursorPosition() const {
        double xPos, yPos;
        glfwGetCursorPos(m_handle, &xPos, &yPos);
        
        return glm::vec2(xPos, yPos);
    }
}