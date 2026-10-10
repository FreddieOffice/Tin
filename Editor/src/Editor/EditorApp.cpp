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

// Too many arguments, will be fixed later
static void CameraInput(Tin::InputHandler& input, Tin::Camera& camera, float deltaTime, bool sceneWindowHovered, glm::vec2 center, float speed, float sensitivity) {
    static bool firstClick = false;

    if (sceneWindowHovered || !firstClick) {
        // Camera rotation with mouse
        if (input.IsMouseButtonPressed(Tin::Enum::MouseButton::RightButton)) {
            input.SetCursorState(Tin::Enum::CursorState::Disabled);

            if (firstClick) {
                input.SetCursorPosition(center);
                firstClick = false;
            }

            glm::vec2 mousePos = input.GetCursorPosition();

            float rotX = sensitivity * (mousePos.y - center.y) / center.y;
            float rotY = sensitivity * (mousePos.x - center.x) / center.x;

            glm::vec3 newOrientation = glm::rotate(camera.Orientation, glm::radians(-rotX), glm::normalize(glm::cross(camera.Orientation, glm::vec3(0.0f, 1.0f, 0.0f))));

            if (abs(glm::angle(newOrientation, glm::vec3(0.0f, 1.0f, 0.0f)) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
                camera.Orientation = newOrientation;
            }

            camera.Orientation = glm::rotate(camera.Orientation, glm::radians(-rotY), glm::vec3(0.0f, 1.0f, 0.0f));

            input.SetCursorPosition(center);
        } else if (input.IsMouseButtonReleased(Tin::Enum::MouseButton::RightButton)) {
            input.SetCursorState(Tin::Enum::CursorState::Normal);
            firstClick = true;
        }

        // Camera speed
        float velocity = speed * deltaTime;
        if (input.IsKeyPressed(Tin::Enum::Key::LeftShift)) {
            velocity = speed * 2.0f * deltaTime;
        }

        // Camera movement in x, z directions
        if (input.IsKeyPressed(Tin::Enum::Key::W)) {
            camera.Position += velocity * camera.Orientation;
        }

        if (input.IsKeyPressed(Tin::Enum::Key::A)) {
            camera.Position += velocity * -glm::normalize(glm::cross(camera.Orientation, glm::vec3(0.0f, 1.0f, 0.0f)));
        }

        if (input.IsKeyPressed(Tin::Enum::Key::S)) {
            camera.Position += velocity * -camera.Orientation;
        }

        if (input.IsKeyPressed(Tin::Enum::Key::D)) {
            camera.Position += velocity * glm::normalize(glm::cross(camera.Orientation, glm::vec3(0.0f, 1.0f, 0.0f)));
        }

        // Camera movement in the y direction
        if (input.IsKeyPressed(Tin::Enum::Key::E)) {
            camera.Position += velocity * glm::vec3(0.0f, 1.0f, 0.0f);
        }

        if (input.IsKeyPressed(Tin::Enum::Key::Q)) {
            camera.Position += velocity * glm::vec3(0.0f, -1.0f, 0.0f);
        }
    }
}

EditorApp::EditorApp() : Application() {

}

EditorApp::~EditorApp() {

}

void EditorApp::Run() {
    srand(time(nullptr));

    Tin::WindowConfig config {
        "Tin Editor",                            // Title
        "assets/textures/smiley.png",            // Icon
        glm::ivec2(1280, 720),                   // Size
        glm::ivec2(-1, -1),                      // Position
        false,                                   // Vsync
        true                                     // Maximized
    };
    Tin::Window window(config);
    Tin::InputHandler inputHandler(window);

    // Renderer setup
    Tin::Renderer renderer(window);

    Tin::Color TinBlue(51, 77, 153); // Tin Blue - a shade of blue endorsed by tin
    Tin::Color EngineBgColor(42, 46, 51);

    Tin::Framebuffer framebuffer(window.GetFramebufferSize());

    Tin::SceneManager sceneManager;

    // Create shaders
    Tin::Shader basicShader(
        Tin::Utils::ReadFile("assets/shaders/basic.vert.glsl"),
        Tin::Utils::ReadFile("assets/shaders/basic.frag.glsl")
    );

    std::vector<std::string> faces = {
        "assets/textures/skybox/BlueSky2/right.jpg",
        "assets/textures/skybox/BlueSky2/left.jpg",
        "assets/textures/skybox/BlueSky2/top.jpg",
        "assets/textures/skybox/BlueSky2/bottom.jpg",
        "assets/textures/skybox/BlueSky2/front.jpg",
        "assets/textures/skybox/BlueSky2/back.jpg"
    };

    /*std::vector<std::string> faces = {
        "assets/textures/skybox/Clear/vz_clear_right.png",
        "assets/textures/skybox/Clear/vz_clear_left.png",
        "assets/textures/skybox/Clear/vz_clear_up.png",
        "assets/textures/skybox/Clear/vz_clear_down.png",
        "assets/textures/skybox/Clear/vz_clear_front.png",
        "assets/textures/skybox/Clear/vz_clear_back.png"
    };*/

    // Create scene
    Tin::Environment environment{Tin::Enum::SkyType::Skybox, faces, TinBlue};
    auto scene = std::make_shared<Tin::Scene>("Scene1", basicShader, environment);
    sceneManager.SetActiveScene(scene);

    // Editor camera
    Tin::Camera camera(window.GetFramebufferSize(), glm::vec3(0.0f, 2.0f, -3.0f), glm::vec3(0.0f, 0.0f, 1.0f), 90.0f, 0.1f, 10000.0f);

    // Create textures and materials
    auto planksTex = std::make_shared<Tin::Texture>("assets/textures/planks.png", Tin::Enum::TextureType::ColorMap);
    auto crateTex = std::make_shared<Tin::Texture>("assets/textures/crate.png", Tin::Enum::TextureType::ColorMap);
    auto containerTex = std::make_shared<Tin::Texture>("assets/textures/container.png", Tin::Enum::TextureType::ColorMap);
    auto container2Tex = std::make_shared<Tin::Texture>("assets/textures/container2.png", Tin::Enum::TextureType::ColorMap);
    auto metalTex = std::make_shared<Tin::Texture>("assets/textures/metal.png", Tin::Enum::TextureType::ColorMap);
    auto metal2Tex = std::make_shared<Tin::Texture>("assets/textures/metal2.png", Tin::Enum::TextureType::ColorMap);
    auto marbleTex = std::make_shared<Tin::Texture>("assets/textures/marble.jpg", Tin::Enum::TextureType::ColorMap);
    auto brickTex = std::make_shared<Tin::Texture>("assets/textures/brick.png", Tin::Enum::TextureType::ColorMap);
    auto brick2Tex = std::make_shared<Tin::Texture>("assets/textures/brick2.jpg", Tin::Enum::TextureType::ColorMap);

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

    Tin::Mesh plane(Tin::Enum::Shape::Block, materials[0]);
    plane.transform.Scale = glm::vec3(20.0f, 0.1f, 20.0f);

    Tin::Mesh box(Tin::Enum::Shape::Block, materials[1]);
    box.transform.Scale = glm::vec3(5.0f, 5.0f, 5.0f);
    box.transform.Position = glm::vec3(0.0f, 7.0f, 0.0f);

    scene->AddMesh(plane);
    scene->AddMesh(box);

    int32_t scale = 20000;
    for (int i = 0; i < 1000; ++i) {
        Tin::Mesh mesh(Tin::Enum::Shape::Block, materials[rand() % materials.size()]);

        mesh.transform.Position = glm::vec3((rand() % scale) - scale / 2, (rand() % scale) - scale / 2, (rand() % scale) - scale / 2);
        mesh.transform.Scale = glm::vec3(1 + rand() % 50, 1 + rand() % 50, 1 + rand() % 50);
        mesh.transform.Rotation = glm::vec3(rand() % 100, rand() % 100, rand() % 100);
        //mesh.material.color = Tin::Color(2 * (1 + rand() % 256), 2 * (1 + rand() % 256), 2 * (1 + rand() % 256));

        scene->AddMesh(mesh);
    }

    // Create skybox
    Tin::Skybox skybox(faces);
    renderer.SetSkybox(std::make_shared<Tin::Skybox>(skybox));

    float cameraSpeed = 20.0f;
    float cameraSensitivity = 180.0f;

    // ImGui
    Gui::SetupImGui(window);

    bool configWindow = true;
    bool aboutWindow = false;
    bool sceneWindowHovered = false;
    bool sceneWindowShown = true;

    // Options
    bool fullscreen = false;
    bool vsync = false;

    float colors[3] = {environment.solidColor.r, environment.solidColor.g, environment.solidColor.b};

    // FPS and delta time stuff
    float deltaTime = 0.0f;
    float lastFrame = static_cast<float>(GetTime());
    float currentFrame = 0.0f;
    float fpsTimer = 0.0f;
    float lastFrame2 = 0.0f;
    int frameCount = 0;
    std::string FPSandMS = "0.0 FPS / 0.0 ms";

    while (window.IsOpen()) {
        PollEvents();
        window.Update();

        // Getting FPS and delta time
        currentFrame = static_cast<float>(GetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        fpsTimer = currentFrame - lastFrame2;
        ++frameCount;

        if (fpsTimer >= 1.0f) {
            FPSandMS = std::to_string((1.0f / fpsTimer) * frameCount) + " FPS / " + std::to_string((fpsTimer / frameCount) * 1000.0f) + " ms";
            lastFrame2 = currentFrame;
            frameCount = 0;
        }

        if (inputHandler.IsKeyPressed(Tin::Enum::Key::LeftControl) && inputHandler.IsKeyPressed(Tin::Enum::Key::X)) {
            window.Close();
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
            ImGui::ColorPicker3("Color", colors);
            ImGui::Separator();

            // Info
            glm::vec2 mousePos = inputHandler.GetCursorPosition();
            ImGui::Text("%s", FPSandMS.c_str());
            ImGui::Text("Mouse pos: %.1f, %.1f", mousePos.x, mousePos.y);
            ImGui::Text("Draw calls: %d", renderer.GetDrawCalls());
            ImGui::Text("Triangle count: %d", renderer.GetTriangleCount());
            ImGui::Separator();

            ImGui::Text("Camera position: %.1f, %.1f, %.1f", camera.Position.x, camera.Position.y, camera.Position.z);
            ImGui::Text("Camera orientation: %.1f, %.1f, %.1f", camera.Orientation.x, camera.Orientation.y, camera.Orientation.z);
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
                window.SetAttribute(Tin::Enum::WindowAttribute::Vsync, vsync);
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
            renderer.SetClearColor(environment.solidColor);
            renderer.Clear();

            // Render
            std::shared_ptr<Tin::Scene> activeScene = sceneManager.GetActiveScene();
            if (activeScene) {
                activeScene->environment.solidColor = Tin::Color(colors[0], colors[1], colors[2]);
                renderer.BeginScene(camera);
                activeScene->Render(renderer);
                renderer.EndScene();
            }

            // Unbind framebuffer, everything is now being rendered to the normal window (for imgui)
            framebuffer.Unbind();
        }

        Gui::Render();

        // Save screenshot
        static bool firstClick = true;

        if (inputHandler.IsKeyPressed(Tin::Enum::Key::J) && firstClick) {
            renderer.SaveScreenshot("Screenshot.png", glm::ivec2(0, 0), window.GetSize());
            firstClick = false;
        }
        else if (inputHandler.IsKeyReleased(Tin::Enum::Key::J)) {
            firstClick = true;
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
