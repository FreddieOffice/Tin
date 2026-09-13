#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/DataStructures/Color.hpp"

namespace Tin {
    Color::Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

    Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

    Color::Color(int32_t r, int32_t g, int32_t b, int32_t a) : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {}

    Color Color::Lerp(const Color& color, float t) const {
        return Color(
            r * (1.0f - t) + color.r * t,
            g * (1.0f - t) + color.g * t,
            b * (1.0f - t) + color.b * t
        );
    }

    Color Color::operator+(const Color& other) const {
        return Color(r + other.r, g + other.g, b + other.b);
    }

    Color Color::operator-(const Color& other) const {
        return Color(r - other.r, g - other.g, b - other.b);
    }

    Color Color::operator*(const Color& other) const {
        return Color(r * other.r, g * other.g, b * other.b);
    }

    Color Color::operator*(float scalar) const {
        return Color(r * scalar, g * scalar, b * scalar);
    }

    Color Color::operator/(const Color& other) const {
        return Color(r / other.r, g / other.g, b / other.b);
    }

    Color Color::operator/(float scalar) const {
        return Color(r / scalar, g / scalar, b / scalar);
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
        if (r == other.r && g == other.g && b == other.b) {
            return true;
        }
        else {
            return false;
        }
    }

    bool Color::operator!=(const Color& other) const {
        if (r != other.r || g != other.g || b != other.b) {
            return true;
        }
        else {
            return false;
        }
    }
}