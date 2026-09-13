#include "Tin/Tin.hpp"
#include "glm/glm.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

int main() {
    Tin::Window win("Hi", glm::vec2(600, 600));
    win.SetIcon("assets/textures/openglmaze/smiley.png");
    Tin::Renderer renderer(win);

    // Set a clear color
    Tin::Color bro(0.2f, 0.3f, 0.6f);
    renderer.ClearColor = bro;

    // ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(win.GetGLFWHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (win.IsOpen()) {
        win.PollEvents();
        win.Update();

        // Rendering code
        renderer.Clear();

        win.SwapBuffers();
    }

    win.Destroy();
    return 0;
}