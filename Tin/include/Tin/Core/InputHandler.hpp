#ifndef TIN_CORE_INPUTHANDLER_HPP
#define TIN_CORE_INPUTHANDLER_HPP

#include "Tin/Core/Window.hpp"

#include "glm/glm.hpp"

namespace Tin {
    namespace Enum {
        // Keyboard keys
        enum class Key {
            Space = 32,
            Apostrophe = 39, /* ' */
            Comma = 44, /* , */
            Minus = 45, /* - */
            Period = 46, /* . */
            Slash = 47, /* / */
            Zero = 48,
            One = 49,
            Two = 50,
            Three = 51,
            Four = 52,
            Five = 53,
            Six = 54,
            Seven = 55,
            Eight = 56,
            Nine = 57,
            Semicolon = 59, /* ; */
            Equal = 61, /* = */
            A = 65,
            B = 66,
            C = 67,
            D = 68,
            E = 69,
            F = 70,
            G = 71,
            H = 72,
            I = 73,
            J = 74,
            K = 75,
            L = 76,
            M = 77,
            N = 78,
            O = 79,
            P = 80,
            Q = 81,
            R = 82,
            S = 83,
            T = 84,
            U = 85,
            V = 86,
            W = 87,
            X = 88,
            Y = 89,
            Z = 90,
            LeftBracket = 91, /* [ */
            Backslash = 92, /* \ */
            RightBracket = 93, /* ] */
            GraveAccent = 96, /* ` */
            World1 = 161, /* non-US #1 */
            World2 = 162, /* non-US #2 */
            Escape = 256,
            Enter = 257,
            Tab = 258,
            Backspace = 259,
            Insert = 260,
            Delete = 261,
            RightArrow = 262,
            LeftArrow = 263,
            DownArrow = 264,
            UpArrow = 265,
            PageUp = 266,
            PageDown = 267,
            Home = 268,
            End = 269,
            CapsLock = 280,
            ScrollLock = 281,
            NumLock = 282,
            PrintScreen = 283,
            Pause = 284,
            F1 = 290,
            F2 = 291,
            F3 = 292,
            F4 = 293,
            F5 = 294,
            F6 = 295,
            F7 = 296,
            F8 = 297,
            F9 = 298,
            F10 = 299,
            F11 = 300,
            F12 = 301,
            F13 = 302,
            F14 = 303,
            F15 = 304,
            F16 = 305,
            F17 = 306,
            F18 = 307,
            F19 = 308,
            F20 = 309,
            F21 = 310,
            F22 = 311,
            F23 = 312,
            F24 = 313,
            F25 = 314,
            Numpad0 = 320,
            Numpad1 = 321,
            Numpad2 = 322,
            Numpad3 = 323,
            Numpad4 = 324,
            Numpad5 = 325,
            Numpad6 = 326,
            Numpad7 = 327,
            Numpad8 = 328,
            Numpad9 = 329,
            NumpadDecimal = 330,
            NumpadDivide = 331,
            NumpadMultiply = 332,
            NumpadSubtract = 333,
            NumpadAdd = 334,
            NumpadEnter = 335,
            NumpadEqual = 336,
            LeftShift = 340,
            LeftControl = 341,
            LeftAlt = 342,
            LeftSuper = 343,
            RightShift = 344,
            RightControl = 345,
            RightAlt = 346,
            RightSuper = 347,
            Menu = 348,
        };

        // Mouse buttons
        enum class MouseButton {
            LeftButton = 0,
            RightButton = 1,
            MiddleButton = 2,
            Button4 = 3,
            Button5 = 4,
            Button6 = 5,
            Button7 = 6,
            Button8 = 7
        };

        enum class CursorState {
            Normal,   // Cursor behaviour is normal
            Hidden,   // Cursor is hidden inside the window
            Disabled, // Cursor is disabled
            Confined  // Cursor is confined to the window
        };
    }

	class InputHandler {
	public:
		explicit InputHandler(const Window& window);

        // Checks if a key has been pressed
        bool IsKeyPressed(Enum::Key key) const;
        // Checks if a mouse button has been pressed
        bool IsMouseButtonPressed(Enum::MouseButton button) const;

        // Checks if a key has been released
        bool IsKeyReleased(Enum::Key key) const;
        // Checks if a mouse button has been released
        bool IsMouseButtonReleased(Enum::MouseButton button) const;

        // Sets the cursors state
        void SetCursorState(Enum::CursorState state);
        // Sets the cursor position
        void SetCursorPosition(glm::vec2 position) const;

        // Returns the cursor state
        Enum::CursorState GetCursorState() const;
        // Returns the cursor position
        glm::vec2 GetCursorPosition() const;
	private:
		GLFWwindow* m_handle;
        Enum::CursorState m_cursorState = Enum::CursorState::Normal;
	};
}

#endif
