#include "Tin/TinPCH.hpp"
#include "Tin/Core/InputHandler.hpp"

namespace Tin {
    InputHandler::InputHandler(const Window& window) : m_handle(window.GetGlfwHandle()) {}

    bool InputHandler::IsKeyPressed(Key key) const {
        return (glfwGetKey(m_handle, static_cast<uint32_t>(key)) == GLFW_PRESS);
    }

    bool InputHandler::IsMouseButtonPressed(MouseButton button) const {
        return (glfwGetMouseButton(m_handle, static_cast<uint32_t>(button)) == GLFW_PRESS);
    }

    bool InputHandler::IsKeyReleased(Key key) const {
        return (glfwGetKey(m_handle, static_cast<uint32_t>(key)) == GLFW_RELEASE);
    }

    bool InputHandler::IsMouseButtonReleased(MouseButton button) const {
        return (glfwGetMouseButton(m_handle, static_cast<uint32_t>(button)) == GLFW_RELEASE);
    }

    void InputHandler::SetCursorState(CursorState state) {
        switch (state) {
        case CursorState::Normal:
            glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;
        case CursorState::Hidden:
            glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            break;
        case CursorState::Disabled:
            glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        case CursorState::Confined:
            glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
            break;
        }

        m_cursorState = state;
    }

    void InputHandler::SetCursorPosition(glm::vec2 position) const {
        glfwSetCursorPos(m_handle, position.x, position.y);
    }

    CursorState InputHandler::GetCursorState() const {
        return m_cursorState;
    }

    glm::dvec2 InputHandler::GetCursorPosition() const {
        glm::dvec2 pos;
        glfwGetCursorPos(m_handle, &pos.x, &pos.y);

        return pos;
    }
}
