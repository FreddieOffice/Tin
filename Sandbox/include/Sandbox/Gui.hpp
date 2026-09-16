#ifndef GUI_HPP
#define GUI_HPP

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Tin/Tin.hpp"

namespace Gui {
    // For docking
    static bool showDockSpace = true;

    void SetupImGui(const Tin::Window& window);

    void MainDockSpace(bool* p_open);

    void NewFrame();

    void Render();

    void Shutdown();
}

#endif