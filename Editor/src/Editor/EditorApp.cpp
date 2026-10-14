// Editor files
#include "Editor/EditorApp.hpp"
#include "Editor/Gui.hpp"

// Everything else
#include "Tin/Core/EntryPoint.hpp"

#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include <iostream>
#include <vector>
#include <array>

// Dedicated GPU preference
//extern "C" __declspec(dllexport) unsigned long NvOptimusEnablement                  = 1;
//extern "C" __declspec(dllexport) unsigned long AmdPowerXpressRequestHighPerformance = 1;

// Too many arguments, will be fixed later
static void CameraInput(Tin::InputHandler& input, Tin::Camera& camera, float deltaTime, bool sceneWindowHovered, glm::vec2 center, float speed, float sensitivity) {
    static bool firstClick = false;

    if (sceneWindowHovered || !firstClick) {
        // Camera rotation with mouse
        if (input.IsMouseButtonPressed(Tin::MouseButton::RightButton)) {
            input.SetCursorState(Tin::CursorState::Disabled);

            if (firstClick) {
                input.SetCursorPosition(center);
                firstClick = false;
            }

            glm::vec2 mousePos = input.GetCursorPosition();

            float rotX = sensitivity * (mousePos.y - center.y) / center.y;
            float rotY = sensitivity * (mousePos.x - center.x) / center.x;

            glm::vec3 newOrientation = glm::rotate(camera.orientation, glm::radians(-rotX), glm::normalize(glm::cross(camera.orientation, glm::vec3(0.0f, 1.0f, 0.0f))));

            if (abs(glm::angle(newOrientation, glm::vec3(0.0f, 1.0f, 0.0f)) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
                camera.orientation = newOrientation;
            }

            camera.orientation = glm::rotate(camera.orientation, glm::radians(-rotY), glm::vec3(0.0f, 1.0f, 0.0f));

            input.SetCursorPosition(center);
        } else if (input.IsMouseButtonReleased(Tin::MouseButton::RightButton)) {
            input.SetCursorState(Tin::CursorState::Normal);
            firstClick = true;
        }

        // Camera speed
        float velocity = speed * deltaTime;
        if (input.IsKeyPressed(Tin::Key::LeftShift)) {
            velocity = speed * 2.0f * deltaTime;
        }

        // Camera movement in x, z directions
        if (input.IsKeyPressed(Tin::Key::W)) {
            camera.position += velocity * camera.orientation;
        }

        if (input.IsKeyPressed(Tin::Key::A)) {
            camera.position += velocity * -glm::normalize(glm::cross(camera.orientation, glm::vec3(0.0f, 1.0f, 0.0f)));
        }

        if (input.IsKeyPressed(Tin::Key::S)) {
            camera.position += velocity * -camera.orientation;
        }

        if (input.IsKeyPressed(Tin::Key::D)) {
            camera.position += velocity * glm::normalize(glm::cross(camera.orientation, glm::vec3(0.0f, 1.0f, 0.0f)));
        }

        // Camera movement in the y direction
        if (input.IsKeyPressed(Tin::Key::E)) {
            camera.position += velocity * glm::vec3(0.0f, 1.0f, 0.0f);
        }

        if (input.IsKeyPressed(Tin::Key::Q)) {
            camera.position += velocity * glm::vec3(0.0f, -1.0f, 0.0f);
        }
    }
}

EditorApp::EditorApp() {

}

EditorApp::~EditorApp() {

}

void EditorApp::Run() {
    srand(time(nullptr));

    Tin::WindowConfig config {
        .title = "Tin Editor",
        .icon = "assets/textures/smiley.png",
        .size = glm::ivec2(1280, 720),
        .position = glm::ivec2(-1, -1),
        .maximized = true,
    };
    Tin::Window window(config);
    Tin::InputHandler inputHandler(window);

    // Renderer setup
    Tin::Renderer renderer;

    Tin::Color TinBlue(51, 77, 153); // Tin Blue - a shade of blue endorsed by tin
    Tin::Color EngineBgColor(42, 46, 51);

    Tin::Framebuffer framebuffer(window.GetFramebufferSize());

    Tin::SceneManager sceneManager;

    // Create shaders
    Tin::Shader basicShader(
        Tin::Utils::ReadFile("assets/shaders/basic.vert.glsl"),
        Tin::Utils::ReadFile("assets/shaders/basic.frag.glsl")
    );

    // Editor camera
    Tin::Camera camera(window.GetFramebufferSize(), glm::vec3(0.0f, 2.0f, -3.0f), glm::vec3(0.0f, 0.0f, 1.0f), 90.0f, 0.1f, 10000.0f);

    /*std::vector<std::string> faces = {
        "assets/textures/skybox/Clear/vz_clear_right.png",
        "assets/textures/skybox/Clear/vz_clear_left.png",
        "assets/textures/skybox/Clear/vz_clear_up.png",
        "assets/textures/skybox/Clear/vz_clear_down.png",
        "assets/textures/skybox/Clear/vz_clear_front.png",
        "assets/textures/skybox/Clear/vz_clear_back.png"
    };*/

    std::vector<std::string> faces = {
        "assets/textures/skybox/Moody/vz_moody_right.png",
        "assets/textures/skybox/Moody/vz_moody_left.png",
        "assets/textures/skybox/Moody/vz_moody_up.png",
        "assets/textures/skybox/Moody/vz_moody_down.png",
        "assets/textures/skybox/Moody/vz_moody_front.png",
        "assets/textures/skybox/Moody/vz_moody_back.png"
    };

    // Create scene
    Tin::Environment environment {
        .type = Tin::SkyType::Skybox,
        .skyboxFaces = faces,
        .solidColor = TinBlue
    };
    auto scene = std::make_shared<Tin::Scene>("Scene1", basicShader, environment);
    sceneManager.SetActiveScene(scene);

    // Create textures and materials
    auto planksTex = std::make_shared<Tin::Texture>("assets/textures/planks.png", Tin::TextureType::ColorMap);
    auto crateTex = std::make_shared<Tin::Texture>("assets/textures/crate.png", Tin::TextureType::ColorMap);
    auto containerTex = std::make_shared<Tin::Texture>("assets/textures/container.png", Tin::TextureType::ColorMap);
    auto container2Tex = std::make_shared<Tin::Texture>("assets/textures/container2.png", Tin::TextureType::ColorMap);
    auto metalTex = std::make_shared<Tin::Texture>("assets/textures/metal.png", Tin::TextureType::ColorMap);
    auto metal2Tex = std::make_shared<Tin::Texture>("assets/textures/metal2.png", Tin::TextureType::ColorMap);
    auto marbleTex = std::make_shared<Tin::Texture>("assets/textures/marble.jpg", Tin::TextureType::ColorMap);
    auto brickTex = std::make_shared<Tin::Texture>("assets/textures/brick.png", Tin::TextureType::ColorMap);
    auto brick2Tex = std::make_shared<Tin::Texture>("assets/textures/brick2.jpg", Tin::TextureType::ColorMap);

    std::vector<Tin::Material> materials = {
        Tin::Material(Tin::Color::White, planksTex),
        Tin::Material(Tin::Color::White, crateTex),
        Tin::Material(Tin::Color::White, containerTex),
        Tin::Material(Tin::Color::White, container2Tex),
        Tin::Material(Tin::Color::White, metalTex),
        Tin::Material(Tin::Color::White, metal2Tex),
        Tin::Material(Tin::Color::White, marbleTex),
        Tin::Material(Tin::Color::White, brickTex),
        Tin::Material(Tin::Color::White, brick2Tex)
    };

    Tin::Mesh plane(Tin::Shape::Block, materials[0]);
    plane.transform.Scale = glm::vec3(20.0f, 0.1f, 20.0f);

    Tin::Mesh box(Tin::Shape::Block, materials[1]);
    box.transform.Scale = glm::vec3(5.0f, 5.0f, 5.0f);
    box.transform.Position = glm::vec3(0.0f, 7.0f, 0.0f);

    scene->AddMesh(plane);
    scene->AddMesh(box);

    int32_t scale = 20000;
    for (int i = 0; i < 1000; ++i) {
        Tin::Mesh mesh(Tin::Shape::Block, materials[rand() % materials.size()]);

        mesh.transform.Position = glm::vec3((rand() % scale) - scale / 2, (rand() % scale) - scale / 2, (rand() % scale) - scale / 2);
        mesh.transform.Scale = glm::vec3(1 + rand() % 150, 1 + rand() % 150, 1 + rand() % 150);
        mesh.transform.Rotation = glm::vec3(rand() % 100, rand() % 100, rand() % 100);
        //mesh.material->color = Tin::Color(2 * (1 + rand() % 256), 2 * (1 + rand() % 256), 2 * (1 + rand() % 256));

        scene->AddMesh(mesh);
    }

    // Create skybox
    auto skybox = std::make_shared<Tin::Skybox>(faces);
    renderer.SetSkybox(skybox);

    float cameraSpeed = 20.0f;
    float cameraSensitivity = 180.0f;

    // ImGui
    Gui::SetupImGui(window);

    bool configWindow = true;
    bool aboutWindow = false;
    bool sceneWindowHovered = false;
    bool sceneWindowShown = true;

    // Options
    bool vsync = false;

    std::array<float, 3> colors = {environment.solidColor.r, environment.solidColor.g, environment.solidColor.b};

    // FPS and delta time stuff
    double deltaTime = 0.0f;
    double lastFrame = GetTime();
    double currentFrame = 0.0f;
    double fpsTimer = 0.0f;
    int frameCount = 0;
    std::string FPSandMS = "0.0 FPS / 0.0 ms";

    while (window.IsOpen()) {
        PollEvents();
        window.Update();

        // Getting delta time
        currentFrame = GetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Update FPS counter
        fpsTimer += deltaTime;
        ++frameCount;

        // Refresh the FPS metrics
        if (fpsTimer >= 1.0) {
            double fps = (1.0 / fpsTimer) * frameCount;
            double ms = fpsTimer / frameCount * 1000.0;

            FPSandMS = std::to_string(fps) + " FPS / " + std::to_string(ms) + " ms";
            fpsTimer -= 1.0;
            frameCount = 0;
        }

        // Render background with a gray color
        renderer.SetClearColor(EngineBgColor);
        renderer.Clear();

        Gui::NewFrame();
        Gui::MainDockSpace(&Gui::showDockSpace);

        // Scene window
        sceneWindowShown = ImGui::Begin(ICON_FA_EYE " Scene");

        ImVec2 windowSize = ImGui::GetContentRegionAvail();
        ImVec2 windowPos = ImGui::GetCursorScreenPos();
        ImVec2 windowCenter(windowPos.x + windowSize.x * 0.5f, windowPos.y + windowSize.y * 0.5f);
        glm::ivec2 framebufferSize = framebuffer.GetSize();

        if (windowSize.x != framebufferSize.x || windowSize.y != framebufferSize.y) {
            framebuffer.Resize(glm::ivec2(windowSize.x, windowSize.y));
            camera.SetViewportSize(glm::ivec2(windowSize.x, windowSize.y));
        }

        // Draw scene to imgui window
        ImGui::Image(static_cast<ImTextureID>(framebuffer.GetTextureId()), windowSize, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
        sceneWindowHovered = ImGui::IsItemHovered(); // Check if mouse is hovering over the image

        // Get client coordinates
        ImVec2 appCoordinates = ImGui::GetMainViewport()->Pos;
        glm::vec2 localCenter(windowCenter.x - appCoordinates.x, windowCenter.y - appCoordinates.y);
        CameraInput(inputHandler, camera, deltaTime, sceneWindowHovered, localCenter, cameraSpeed, cameraSensitivity);

        ImGui::End();

        // Config window
        if (configWindow) {
            ImGui::Begin(ICON_FA_GEAR " Tin", &configWindow);

            ImGui::Text("Tin Engine");
            ImGui::Separator();

            ImGui::Text("Background color picker");
            ImGui::ColorPicker3("Color", colors.data());
            ImGui::Separator();

            // Info
            glm::dvec2 mousePos = inputHandler.GetCursorPosition();
            ImGui::Text("%s", FPSandMS.c_str());
            ImGui::Text("Mouse pos: %.1d, %.1d", mousePos.x, mousePos.y);
            ImGui::Text("Draw calls: %d", renderer.GetDrawCalls());
            ImGui::Text("Triangle count: %d", renderer.GetTriangleCount());
            ImGui::Separator();

            ImGui::Text("Camera position: %.1f, %.1f, %.1f", camera.position.x, camera.position.y, camera.position.z);
            ImGui::Text("Camera orientation: %.1f, %.1f, %.1f", camera.orientation.x, camera.orientation.y, camera.orientation.z);
            ImGui::SliderFloat("Camera speed", &cameraSpeed, 1.0f, 100.0f);
            ImGui::SliderFloat("Camera sensitivity", &cameraSensitivity, 1.0f, 200.0f);

            ImGui::End();
        }

        if (aboutWindow) {
            ImGui::Begin(ICON_FA_CIRCLE_INFO " About Tin Engine", &aboutWindow);

            ImGui::TextColored(ImVec4(0.2f, 0.3f, 0.6f, 1.0f), "Tin Engine");
            ImGui::SeparatorText(" Info ");
            ImGui::TextWrapped(
                "This is my 4th attempt at making a game engine\n"
                "The first ever version was called SmileyBox3D\n"
                "Version: pre-alpha"
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
                window.SetAttribute(Tin::WindowAttribute::Vsync, vsync);
            };

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("About")) {
            if (ImGui::MenuItem("About window")) {
                aboutWindow = true;
            }

            if (ImGui::MenuItem("Visit git repository")) {
                std::system("start https://github.com/FreddieOffice/Tin/tree/main");
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();

        // Rendering code
        // Only render if the scene window is shown
        if (sceneWindowShown) {
            // Bind the framebuffer, everything is now being rendered to a texture
            framebuffer.Bind();
            renderer.SetViewportSize(framebuffer.GetSize());

            // Render active scene
            std::shared_ptr<Tin::Scene> activeScene = sceneManager.GetActiveScene();
            if (activeScene) {
                activeScene->environment.solidColor = Tin::Color(colors[0], colors[1], colors[2]);
                renderer.BeginScene(camera);
                activeScene->Render(renderer);
                renderer.EndScene();

                // // Temporary solution
                if (activeScene->environment.type == Tin::SkyType::Skybox) {
                    renderer.RenderSkybox();
                }
            }

            // Unbind framebuffer, everything is now being rendered to the normal window (for imgui)
            framebuffer.Unbind();
        }

        Gui::Render();

        // Screenshot
        bool click = true;
        if (inputHandler.IsKeyPressed(Tin::Key::J) && click) {
            renderer.SaveScreenshot("Screenshot.png", glm::ivec2(0, 0), window.GetFramebufferSize());
            click = false;
        } else if (inputHandler.IsKeyReleased(Tin::Key::J)) {
            click = true;
        }

        window.SwapBuffers();
    }

    // Cleanup
    Gui::Shutdown();

    sceneManager.Destroy();
    window.Destroy();
}

// Send the editor app over to Tin
std::unique_ptr<Tin::Application> Tin::CreateApplication() {
    return std::make_unique<EditorApp>();
}
