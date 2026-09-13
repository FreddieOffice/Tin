#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

// Material uniforms
uniform vec3 Color;
//uniform sampler2D ColorMap;

//uniform bool HasColorMap;

void main() {
    FragColor = vec4(Color, 1.0);
}