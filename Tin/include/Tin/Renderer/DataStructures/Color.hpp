#ifndef TIN_RENDERER_DATASTRUCTURES_COLOR_HPP
#define TIN_RENDERER_DATASTRUCTURES_COLOR_HPP

#include <cstdint>

namespace Tin {
    struct Color {
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 1.0f;

        // Default constructor
        // Color is black
        Color() = default;
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

        // Predefined colors

        static Color Transparent;
        static Color Azure;
        static Color Beige;
        static Color Black;
        static Color Blue;
        static Color Brown;
        static Color Crimson;
        static Color Cyan;
        static Color DarkGreen;
        static Color DarkMagenta;
        static Color Gray;
        static Color Green;
        static Color Indigo;
        static Color Lavender;
        static Color Magenta;
        static Color Maroon;
        static Color Mint;
        static Color NavyBlue;
        static Color Olive;
        static Color Orange;
        static Color Purple;
        static Color Red;
        static Color Teal;
        static Color Turquoise;
        static Color Violet;
        static Color White;
        static Color Yellow;
    };
}

#endif
