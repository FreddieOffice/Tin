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

// Camera
void cameraInput(Tin::InputHandler& input, Tin::Camera& camera, float deltaTime) {
    float speed = 5.0f * deltaTime;
    float sensitivity = 130.0f;
    bool firstClick = false;

    glm::vec2 size = camera.GetViewportSize();
    int32_t width = size.x;
    int32_t height = size.y;

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
        speed = 0.1f * deltaTime;
    }
    else if (input.IsKeyReleased(Tin::Enum::Key::KEY_LEFT_SHIFT)) {
        speed = 0.05f * deltaTime;
    }

    if (ImGui::GetIO().WantCaptureMouse) {
        return;
    }

    // Camera rotation with mouse
    if (input.IsMouseButtonPressed(Tin::Enum::MouseButton::MOUSE_BUTTON_LEFT))
    {
        input.SetCursorState(Tin::Enum::CursorState::DISABLED);

        if (firstClick)
        {
            input.SetCursorPosition(glm::vec2(width / 2, height / 2));
            firstClick = false;
        }

        glm::vec2 mousePos = input.GetCursorPosition();

        float rotX = sensitivity * (float)(mousePos.y - (height / 2)) / height;
        float rotY = sensitivity * (float)(mousePos.x - (width / 2)) / width;

        glm::vec3 newOrientation = glm::rotate(camera.Orientation, glm::radians(-rotX), glm::normalize(glm::cross(camera.Orientation, glm::vec3(0.0f, 1.0f, 0.0f))));

        if (abs(glm::angle(newOrientation, glm::vec3(0.0f, 1.0f, 0.0f)) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            camera.Orientation = newOrientation;
        }

        camera.Orientation = glm::rotate(camera.Orientation, glm::radians(-rotY), glm::vec3(0.0f, 1.0f, 0.0f));

        input.SetCursorPosition(glm::vec2(width / 2, height / 2));
    }
    else if (input.IsMouseButtonReleased(Tin::Enum::MouseButton::MOUSE_BUTTON_LEFT))
    {
        input.SetCursorState(Tin::Enum::CursorState::NORMAL);
        firstClick = true;
    }
}

std::vector<Tin::Vertex> vertices = {
    Tin::Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
    Tin::Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)),
    Tin::Vertex(glm::vec3( 0.0f,  0.5f, 0.0f), glm::vec2(0.5f, 1.0f))
};

std::vector<unsigned int> indices = {
    0, 1, 2
};

App* App::GetInstance() {
    static App instance; 
    return &instance;
}

// main

int App::Run() {
    Tin::Window window("Very Happy Smiley Game 2!", glm::vec2(600, 600));
    window.SetIcon("assets/textures/openglmaze/smiley.png");

    Tin::InputHandler inputHandler(window);

    Tin::Renderer renderer(window);

    // Set a clear color
    Tin::Color bro(0.2f, 0.3f, 0.6f);
    renderer.ClearColor = bro;

    Tin::Shader shader("assets/shaders/default.vert", "assets/shaders/default.frag");

    Tin::Material material(Tin::Colors::White, "assets/textures/metal.png");

    Tin::Camera camera(window.GetSize(), glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    Tin::Mesh mesh(vertices, indices, shader, material);

    // ImGui
    Gui::SetupImGui(window);

    bool showDockSpace = true;
    bool backgroundColorWindow = false;
    bool aboutWindow = false;

    bool wireframeMode = false;

    float colors[3] = {renderer.ClearColor.r, renderer.ClearColor.g, renderer.ClearColor.b};

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (window.IsOpen()) {
        window.PollEvents();
        window.Update();

        float currentFrame = static_cast<float>(window.GetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (inputHandler.IsKeyPressed(Tin::Enum::KEY_J)) {
            window.SetTitle("Test");
        }
        
        // Rendering code
        renderer.Clear();
        renderer.ClearColor = Tin::Color(colors[0], colors[1], colors[2]);

        // Update camera
        camera.SetViewportSize(window.GetSize());
        cameraInput(inputHandler, camera, deltaTime);
        camera.UpdateMatrix(shader);

        mesh.Draw();

        // ImGui
        Gui::NewFrame();

        Gui::MainDockSpace(&showDockSpace);

        ImGui::BeginMainMenuBar();

        if (ImGui::BeginMenu("File")) {
            // things will be added here some day
            if (ImGui::MenuItem("New scene")) {

            }
            if (ImGui::MenuItem("Save scene")) {

            }
            if (ImGui::MenuItem("Load scene")) {

            }

            ImGui::Separator();

            if (ImGui::MenuItem("Exit")) {
                window.Destroy();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Render")) {
            if (ImGui::MenuItem("Background color")) {
                backgroundColorWindow = true;
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Wireframe mode", NULL, &wireframeMode)) {
                if (wireframeMode == true) {
                    renderer.SetPolygonMode(Tin::Enum::PolygonMode::WIREFRAME);
                }
                else {
                    renderer.SetPolygonMode(Tin::Enum::PolygonMode::NORMAL);
                }
            }

            ImGui::EndMenu();
        }

        if (backgroundColorWindow == true) {
            ImGui::Begin("Background color picker", &backgroundColorWindow);
            ImGui::SetWindowSize(ImVec2(250, 250));
            ImGui::ColorPicker3("Color", colors);
            ImGui::End();
        }

        if (aboutWindow == true) {
            ImGui::Begin("About the Tin Engine", &aboutWindow);
            ImGui::SetWindowSize(ImVec2(500, 500));
            ImGui::TextColored(ImVec4(0.1f, 0.4f, 0.8f, 1.0f), "Tin Engine");
            ImGui::SeparatorText(" Info ");
            ImGui::TextWrapped(
                "4th attempt at making a game engine\n"
                "The first ever version was called SmileyBox3D\n"
                "Version: pre-alpha"
            );
            ImGui::End();
        }

        ImGui::EndMainMenuBar();

        Gui::Render();

        window.SwapBuffers();
    }

    // Cleanup
    Gui::Shutdown();

    window.Destroy();
    return 0;
}