#ifndef TIN_RENDERER_DATASTRUCTURES_COLOR_HPP
#define TIN_RENDERER_DATASTRUCTURES_COLOR_HPP

#include <cstdint>

namespace Tin {
	struct Color {
        float r, g, b, a;

        // Default constructor
        // Color is black
        Color();
        // Creates a color from floats
        Color(float r, float g, float b, float a = 1.0f);
        // Creates a color from RGB values
        Color(int32_t r, int32_t g, int32_t b, int32_t a = 255);

        // Returns a color interpolated between two colors
        Color Lerp(const Color& other, float t) const;

        // Operators

        Color operator+(const Color& other) const;
        Color operator-(const Color& other) const;
        Color operator*(const Color& other) const;
        Color operator*(float scalar) const;
        Color operator/(const Color& other) const;
        Color operator/(float scalar) const;

        Color& operator+=(const Color& other);
        Color& operator-=(const Color& other);
        Color& operator*=(const Color& other);
        Color& operator*=(float scalar);
        Color& operator/=(const Color& other);
        Color& operator/=(float scalar);

        bool operator==(const Color& other) const;
        bool operator!=(const Color& other) const;
	};

    // Predefined colors
    namespace Colors {
        static const Color Black = Color(0.0f, 0.0f, 0.0f);

        static const Color DarkRed = Color(0.5f, 0.0f, 0.0f);
        static const Color Red = Color(1.0f, 0.0f, 0.0f);

        static const Color DarkGreen = Color(0.0f, 0.5f, 0.0f);
        static const Color Green = Color(0.0f, 1.0f, 0.0f);

        static const Color DarkBlue = Color(0.0f, 0.0f, 0.5f);
        static const Color Blue = Color(0.0f, 0.0f, 1.0f);

        static const Color Orange = Color(1.0f, 0.5f, 0.0f);
        static const Color Brown = Color(0.6f, 0.3f, 0.0f);
        static const Color DarkYellow = Color(0.5f, 0.5f, 0.0f);
        static const Color Yellow = Color(1.0f, 1.0f, 0.0f);

        static const Color Purple = Color(0.5f, 0.0f, 0.5f);
        static const Color Magenta = Color(1.0f, 0.0f, 1.0f);

        static const Color DarkCyan = Color(0.0f, 0.5f, 0.5f);
        static const Color Cyan = Color(0.0f, 1.0f, 1.0f);

        static const Color Gray = Color(0.5f, 0.5f, 0.5f);
        static const Color White = Color(1.0f, 1.0f, 1.0f);
    }
}

#endif