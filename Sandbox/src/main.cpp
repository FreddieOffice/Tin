#include "Tin/Tin.hpp"
#include "glm/glm.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <vector>

std::vector<Tin::Vertex> vertices = {
    Tin::Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
    Tin::Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)),
    Tin::Vertex(glm::vec3( 0.0f,  0.5f, 0.0f), glm::vec2(0.5f, 1.0f))
};

std::vector<unsigned int> indices = {
    0, 1, 2
};

int main() {
    Tin::Window window("Very Happy Smiley Game 2!", glm::vec2(600, 600));
    window.SetIcon("assets/textures/openglmaze/smiley.png");

    Tin::InputHandler input(window);

    Tin::Renderer renderer(window);

    // Set a clear color
    Tin::Color bro(0.2f, 0.3f, 0.6f);
    renderer.ClearColor = bro;

    // ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.GetGLFWHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Tin::Shader shader("assets/shaders/default.vert", "assets/shaders/default.frag");

    Tin::Material material(Tin::Colors::White, "assets/textures/metal.png");

    Tin::Mesh mesh(vertices, indices, shader, material);

    while (window.IsOpen()) {
        window.PollEvents();
        window.Update();

        if (input.IsKeyPressed(Tin::Enum::KEY_J)) {
            window.SetTitle("Test");
        }
        
        // Rendering code
        renderer.Clear();

        mesh.Draw();

        window.SwapBuffers();
    }

    window.Destroy();
    return 0;
}