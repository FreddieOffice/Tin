// Project files
#include "App.hpp"
#include "Gui.hpp"

// Everything else

#include "Tin/Tin.hpp"

#include <iostream>
#include <vector>

#include "glm/glm.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

static void cameraInput(Tin::InputHandler& input, Tin::Camera& camera, float deltaTime, bool sceneWindowHovered, glm::vec2 center) {
    static float speed = 5.0f * deltaTime;
    static float sensitivity = 180.0f * deltaTime;
    static bool firstClick = false;

    if (sceneWindowHovered | !firstClick) {
        // Camera rotation with mouse
        if (input.IsMouseButtonPressed(Tin::Enum::MouseButton::MOUSE_BUTTON_RIGHT)) {
            input.SetCursorState(Tin::Enum::CursorState::DISABLED);

            if (firstClick)
            {
                input.SetCursorPosition(center);
                firstClick = false;
            }

            glm::vec2 mousePos = input.GetCursorPosition();

            float rotX = sensitivity * (float)(mousePos.y - center.y) / center.y;
            float rotY = sensitivity * (float)(mousePos.x - center.x) / center.x;

            glm::vec3 newOrientation = glm::rotate(camera.Orientation, glm::radians(-rotX), glm::normalize(glm::cross(camera.Orientation, glm::vec3(0.0f, 1.0f, 0.0f))));

            if (abs(glm::angle(newOrientation, glm::vec3(0.0f, 1.0f, 0.0f)) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                camera.Orientation = newOrientation;
            }

            camera.Orientation = glm::rotate(camera.Orientation, glm::radians(-rotY), glm::vec3(0.0f, 1.0f, 0.0f));

            input.SetCursorPosition(center);
        }
        else if (input.IsMouseButtonReleased(Tin::Enum::MouseButton::MOUSE_BUTTON_RIGHT)) {
            input.SetCursorState(Tin::Enum::CursorState::NORMAL);
            firstClick = true;
        }

        // Camera movement in x, z directions
        if (input.IsKeyPressed(Tin::Enum::Key::KEY_W)) {
            camera.Position += speed * camera.Orientation;
        }

        if (input.IsKeyPressed(Tin::Enum::Key::KEY_A)) {
            camera.Position += speed * -glm::normalize(glm::cross(camera.Orientation, glm::vec3(0.0f, 1.0f, 0.0f)));
        }

        if (input.IsKeyPressed(Tin::Enum::Key::KEY_S)) {
            camera.Position += speed * -camera.Orientation;
        }

        if (input.IsKeyPressed(Tin::Enum::Key::KEY_D)) {
            camera.Position += speed * glm::normalize(glm::cross(camera.Orientation, glm::vec3(0.0f, 1.0f, 0.0f)));
        }

        // Camera movement in the y direction
        if (input.IsKeyPressed(Tin::Enum::Key::KEY_E)) {
            camera.Position += speed * glm::vec3(0.0f, 1.0f, 0.0f);
        }

        if (input.IsKeyPressed(Tin::Enum::Key::KEY_Q)) {
            camera.Position += speed * glm::vec3(0.0f, -1.0f, 0.0f);
        }

        // Camera speed
        if (input.IsKeyPressed(Tin::Enum::Key::KEY_LEFT_SHIFT)) {
            speed = 30.0f * deltaTime;
        }
        else if (input.IsKeyReleased(Tin::Enum::Key::KEY_LEFT_SHIFT)) {
            speed = 5.0f * deltaTime;
        }
    }
}

App* App::GetInstance() {
    static App instance; 
    return &instance;
}

int App::Run() {
    srand(time(NULL));

    Tin::WindowConfig config{
        "Tin Editor",                            // Title
        "assets/textures/openglmaze/smiley.png", // Icon
        glm::vec2(1280, 720),                    // Size
        glm::vec2(-1, -1),                       // Position
        false,                                   // Vsync
        true                                     // Maximized
    };
    Tin::Window window(config);

    Tin::InputHandler inputHandler(window);

    Tin::Renderer renderer(window);
    Tin::Color TinBlue(0.2f, 0.3f, 0.6f); // Tin Blue - a shade of blue endorsed by tin
    renderer.ClearColor = TinBlue;

    Tin::Framebuffer framebuffer(window.GetSize());

    Tin::Scene scene;

    Tin::Shader shader("assets/shaders/default.vert", "assets/shaders/default.frag");
    //Tin::Shader skyboxShader("assets/shaders/skybox.vert", "assets/shaders/skybox.frag");

    // Editor camera
    Tin::Camera camera(window.GetSize(), glm::vec3(0.0f, 2.0f, -3.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    std::vector<Tin::Material> materials = {
        Tin::Material(Tin::Colors::White, "assets/textures/crate.png"),
        Tin::Material(Tin::Colors::White, "assets/textures/container.png"),
        Tin::Material(Tin::Colors::White, "assets/textures/container2.png"),
        Tin::Material(Tin::Colors::White, "assets/textures/metal.png"),
        Tin::Material(Tin::Colors::White, "assets/textures/metal2.png"),
        Tin::Material(Tin::Colors::White, "assets/textures/marble.jpg"),
        Tin::Material(Tin::Colors::White, "assets/textures/brick.png"),
        Tin::Material(Tin::Colors::White, "assets/textures/brick2.jpg"),
        Tin::Material(Tin::Colors::White, "assets/textures/openglmaze/smiley.png"),
    };

    // Tin::Mesh mesh(vertices, indices, shader, material);

    for (int i = 0; i < 1000; i++) {
        Tin::Mesh mesh(static_cast<Tin::Enum::Shape>(1 + rand() % 3), shader, materials[rand() % materials.size()]);

        mesh.transform.Position = glm::vec3((rand() % 100) - 50, (rand() % 100) - 50, 100 - (rand() % 100) - 50);
        mesh.transform.Scale = glm::vec3(1 + rand() % 6, 1 + rand() % 6, 1 + rand() % 6);
        // mesh.transform.Rotation = glm::vec3(rand() % 100, rand() % 100, rand() % 100);
        mesh.material.color = Tin::Color(1 + rand() % 256, 1 + rand() % 256, 1 + rand() % 256);

        scene.AddMesh(mesh);
    }

    // ImGui
    Gui::SetupImGui(window);

    bool configWindow = true;
    bool aboutWindow = false;
    float sceneWindowHovered = false;

    // Options
    bool fullscreen = false;
    bool vsync = false;

    float colors[3] = {renderer.ClearColor.r, renderer.ClearColor.g, renderer.ClearColor.b};

    // FPS and delta time stuff
    float deltaTime = 0.0f, lastFrame = 0.0f, currentFrame = 0.0f; // Delta time
    float fpsTimer = 0.0f, lastFrame2 = 0.0f; // For fps, idk how else to name these
    int frameCount = 0;
    std::string FPSandMS = "0.0 FPS / 0.0 ms";

    while (window.IsOpen()) {
        window.PollEvents();
        window.Update();
        renderer.Clear();

        // Getting FPS and delta time
        currentFrame = static_cast<float>(window.GetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        fpsTimer = currentFrame - lastFrame2;
        frameCount++;

        if (fpsTimer >= 1.0f) {
            FPSandMS = std::to_string((1.0f / fpsTimer) * frameCount) + " FPS / " + std::to_string((fpsTimer / frameCount) * 1000.0f) + " ms";
            lastFrame2 = currentFrame;
            frameCount = 0;
        }

        if (inputHandler.IsKeyPressed(Tin::Enum::Key::KEY_LEFT_CONTROL) && inputHandler.IsKeyPressed(Tin::Enum::Key::KEY_X)) {
            window.Close();
        }

        // Gui
        Gui::NewFrame();
        Gui::MainDockSpace(&Gui::showDockSpace);

        // Scene window
        ImGui::Begin("Scene");

        ImVec2 windowSize = ImGui::GetContentRegionAvail();
        ImVec2 windowPos = ImGui::GetCursorScreenPos();
        ImVec2 windowCenter(windowPos.x + windowSize.x * 0.5f, windowPos.y + windowSize.y * 0.5f);
        
        framebuffer.Resize(glm::vec2(windowSize.x, windowSize.y));
        camera.SetViewportSize(glm::vec2(windowSize.x, windowSize.y));

        // Draw scene to imgui window
        ImGui::Image((void*)(uintptr_t)framebuffer.GetTextureID(), ImVec2(windowSize.x, windowSize.y), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));

        // Get client coordinates
        ImVec2 appCoordinates = ImGui::GetMainViewport()->Pos;
        glm::vec2 localCenter(windowCenter.x - appCoordinates.x, windowCenter.y - appCoordinates.y);
        cameraInput(inputHandler, camera, deltaTime, sceneWindowHovered, localCenter);

        sceneWindowHovered = ImGui::IsItemHovered(); // Check if mouse is hovering over the image

        ImGui::End();

        // Config window
        if (configWindow == true) {
            ImGui::Begin("Tin", &configWindow);
            ImGui::SetWindowSize(ImVec2(300, 600));

            ImGui::Text("Tin Engine");
            ImGui::Separator();

            ImGui::Text("Background color picker");
            ImGui::ColorPicker3("Color", colors);
            ImGui::Separator();

            // Info
            glm::vec2 mousePos = inputHandler.GetCursorPosition();
            ImGui::Text("%s", FPSandMS.c_str());
            ImGui::Text("Mouse pos: %.1f, %.1f", mousePos.x, mousePos.y);
            ImGui::Text("Camera position: %.1f, %.1f, %.1f", camera.Position.x, camera.Position.y, camera.Position.z);
            ImGui::Text("Camera orientation: %.1f, %.1f, %.1f", camera.Orientation.x, camera.Orientation.y, camera.Orientation.z);

            ImGui::End();
        }

        if (aboutWindow == true) {
            ImGui::Begin("About Tin Engine", &aboutWindow);

            ImGui::SetWindowSize(ImVec2(500, 500));
            ImGui::TextColored(ImVec4(0.2f, 0.3f, 0.6f, 1.0f), "Tin Engine");
            ImGui::SeparatorText(" Info ");
            ImGui::TextWrapped(
                "This is my 4th attempt at making a game engine\n"
                "The first ever version was called SmileyBox3D\n"
                "Version: pre-pre-alpha"
            );

            ImGui::End();
        }

        // Menu bar
        ImGui::BeginMainMenuBar();

        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New scene")) {

            }
            if (ImGui::MenuItem("Save scene")) {

            }
            if (ImGui::MenuItem("Load scene")) {

            }

            ImGui::Separator();

            if (ImGui::MenuItem("Exit", "CTRL + X")) {
                window.Close();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Render")) {
            if (ImGui::MenuItem("Config window")) {
                configWindow = true;
            };

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Options")) {
            if (ImGui::MenuItem("Vsync", "", &vsync)) {
                window.SetSetting(Tin::Enum::WindowSetting::VSYNC, vsync);
            };

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("About")) {
            if (ImGui::MenuItem("About window")) {
                aboutWindow = true;
            }

            if (ImGui::MenuItem("Visit website")) {
                std::system("start https://maxdisk.github.io/");
            }

            if (ImGui::MenuItem("Visit git repository")) {
                std::system("start https://github.com/FreddieOffice/Tin/tree/main");
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();

        ImGui::Render();

        // Rendering code
        framebuffer.Bind();
        renderer.SetViewportSize(framebuffer.GetSize());

        renderer.Clear();
        renderer.ClearColor = Tin::Color(colors[0], colors[1], colors[2]);

        // Update camera
        camera.UpdateMatrix(shader, camera.GetProjectionMatrix(), camera.GetViewMatrix());

        scene.Draw();

        framebuffer.Unbind();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 

        // Save screenshot
        static bool firstClick = true;

        if (inputHandler.IsKeyPressed(Tin::Enum::Key::KEY_J) && firstClick) {
            renderer.SaveScreenshot("Screenshot.png", glm::vec2(0, 0), window.GetSize());
            firstClick = false;
        }
        else if (inputHandler.IsKeyReleased(Tin::Enum::Key::KEY_J)) {
            firstClick = true;
        }

        window.SwapBuffers();
    }

    // Cleanup
    Gui::Shutdown();

    window.Destroy();
    return 0;
}