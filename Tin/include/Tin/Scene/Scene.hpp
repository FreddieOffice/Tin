#ifndef TIN_SCENE_HPP
#define TIN_SCENE_HPP

#include "Tin/Renderer/Objects/Mesh.hpp"
#include "Tin/Renderer/Objects/Camera.hpp"

#include <vector>

namespace Tin {
    class Scene {
    public:
        Scene();

        // Renders the scene
        void Draw();
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
    };
}

#endif