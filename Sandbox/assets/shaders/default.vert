#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 Model;
uniform mat4 CamProjection;
uniform mat4 CamView;

void main() {
    gl_Position = CamProjection * CamView * Model * vec4(aPos, 1.0);

    TexCoord = aTexCoord;
}