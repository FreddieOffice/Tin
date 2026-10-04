#ifndef TIN_SCENE_HPP
#define TIN_SCENE_HPP

#include "Tin/Renderer/Objects/Mesh.hpp"
#include "Tin/Renderer/Objects/Camera.hpp"
#include "Tin/Renderer/Renderer.hpp"

#include <vector>

namespace Tin {
    namespace Enum {
        enum class SkyType {
            Skybox,
            SolidColor
        };
    }

    struct Environment {
        Enum::SkyType type;
        std::vector<std::string> skyboxFaces;
        Color solidColor;
    };

    class Scene {
    public:
        Environment environment;
        Scene(const Shader& basicShader, const Environment& environment);

        // Renders the scene
        void Render(Renderer& renderer, Camera& camera);
        // Destroys the scene
        void Destroy();

        // Adds a mesh to the scene
        void AddMesh(const Mesh& mesh);
        // Adds meshes to the scene
        void AddMeshes(const std::vector<Mesh>& meshes);
        // Deletes a mesh from the scene
        //void DeleteMesh(const Mesh& mesh);

        // Retrieves a mesh from the scene
        //Mesh& GetMesh(const Mesh& mesh);
        // Returns the meshes that are in the scene
        std::vector<Mesh>& GetMeshes();
    private:
        std::vector<Mesh> m_meshes;
        Shader m_basicShader;
    };
}

#endif