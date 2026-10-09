#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/DataStructures/Color.hpp"

namespace Tin {
    Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

    Color::Color(int32_t r, int32_t g, int32_t b, int32_t a) : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {}

    Color Color::Lerp(const Color& color, float t) const {
        return Color(
            r * (1.0f - t) + color.r * t,
            g * (1.0f - t) + color.g * t,
            b * (1.0f - t) + color.b * t,
            a * (1.0f - t) + color.b * t
        );
    }

    Color Color::operator+(const Color& other) const {
        return Color(r + other.r, g + other.g, b + other.b, a + other.a);
    }

    Color Color::operator-(const Color& other) const {
        return Color(r - other.r, g - other.g, b - other.b, a - other.a);
    }

    Color Color::operator*(const Color& other) const {
        return Color(r * other.r, g * other.g, b * other.b, a * other.a);
    }

    Color Color::operator*(float scalar) const {
        return Color(r * scalar, g * scalar, b * scalar, a * scalar);
    }

    Color Color::operator/(const Color& other) const {
        return Color(r / other.r, g / other.g, b / other.b, a / other.a);
    }

    Color Color::operator/(float scalar) const {
        return Color(r / scalar, g / scalar, b / scalar, a / scalar);
    }

    Color& Color::operator+=(const Color& other) {
        return *this = *this + other;
    }

    Color& Color::operator-=(const Color& other) {
        return *this = *this - other;
    }

    Color& Color::operator*=(const Color& other) {
        return *this = *this * other;
    }

    Color& Color::operator*=(float scalar) {
        return *this = *this * scalar;
    }

    Color& Color::operator/=(const Color& other) {
        return *this = *this / other;
    }

    Color& Color::operator/=(float scalar) {
        return *this = *this / scalar;
    }

    bool Color::operator==(const Color& other) const {
        if (r == other.r && g == other.g && b == other.b && a == other.a) {
            return true;
        } else {
            return false;
        }
    }

    bool Color::operator!=(const Color& other) const {
        if (r != other.r || g != other.g || b != other.b || a != other.a) {
            return true;
        } else {
            return false;
        }
    }

    // Predefined colors

    Color Color::Transparent = Color(0.0f, 0.0f, 0.0f, 0.0f);
    Color Color::Azure = Color(0.0f, 0.5f, 1.0f);
    Color Color::Beige = Color(0.95f, 0.95f, 0.85f);
    Color Color::Black = Color(0.0f, 0.0f, 0.0f);
    Color Color::Blue = Color(0.0f, 0.0f, 1.0f);
    Color Color::Brown = Color(0.6f, 0.3f, 0.0f);
    Color Color::Crimson = Color(0.86f, 0.07f, 0.23f);
    Color Color::Cyan = Color(0.0f, 1.0f, 1.0f);
    Color Color::DarkGreen = Color(0.0f, 0.5f, 0.0f);
    Color Color::Gray = Color(0.5f, 0.5f, 0.5f);
    Color Color::Green = Color(0.0f, 1.0f, 0.0f);
    Color Color::Indigo = Color(0.25f, 0.0f, 1.0f);
    Color Color::Lavender = Color(0.71f, 0.49f, 0.86f);
    Color Color::Magenta = Color(1.0f, 0.0f, 1.0f);
    Color Color::Maroon = Color(0.5f, 0.0f, 0.0f);
    Color Color::Mint = Color(0.74f, 0.99f, 0.79f);
    Color Color::NavyBlue = Color(0.0f, 0.0f, 0.5f);
    Color Color::Olive = Color(0.5f, 0.5f, 0.0f);
    Color Color::Orange = Color(1.0f, 0.5f, 0.0f);
    Color Color::Purple = Color(0.5f, 0.0f, 0.5f);
    Color Color::Red = Color(1.0f, 0.0f, 0.0f);
    Color Color::Teal = Color(0.0f, 0.5f, 0.5f);
    Color Color::Turquoise = Color(0.25f, 0.87f, 0.81f);
    Color Color::Violet = Color(0.6f, 0.0f, 1.0f);
    Color Color::White = Color(1.0f, 1.0f, 1.0f);
    Color Color::Yellow = Color(1.0f, 1.0f, 0.0f);
}