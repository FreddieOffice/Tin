#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

// Material uniforms
uniform vec3 Color;
uniform sampler2D ColorMap;

uniform bool HasColorMap;

void main() {
    vec4 FinalColor;

    if (HasColorMap) {
        FinalColor = texture(ColorMap, TexCoord) * vec4(Color, 1.0);
    }
    else {
        FinalColor = vec4(Color, 1.0);
    }

    FragColor = FinalColor;
}