#include "Tin/Tin.hpp"
#include "glm/glm.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

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

    while (window.IsOpen()) {
        window.PollEvents();
        window.Update();

        if (input.IsKeyPressed(Tin::Enum::KEY_J)) {
            window.SetTitle("Test");
        }

        // Rendering code
        renderer.Clear();

        window.SwapBuffers();
    }

    window.Destroy();
    return 0;
}