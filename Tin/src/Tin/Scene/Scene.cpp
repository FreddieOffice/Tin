#include "Tin/TinPCH.hpp"
#include "Tin/Scene/Scene.hpp"

namespace Tin {
    Scene::Scene() {

    }

    void Scene::Draw() {
        for (Mesh& mesh : m_meshes) {
            mesh.Draw();
        }
    }

    void Scene::Destroy() {
        for (Mesh& mesh : m_meshes) {
            mesh.Destroy();
        }

        m_meshes.clear();
    }

    void Scene::AddMesh(const Mesh& mesh) {
        m_meshes.push_back(mesh);
    }

    void Scene::AddMeshes(const std::vector<Mesh>& meshes) {
        m_meshes.insert(m_meshes.end(), meshes.begin(), meshes.end());
    }

    /*void Scene::DeleteMesh(const Mesh& mesh) { 
        auto it = std::find(m_meshes.begin(), m_meshes.end(), mesh);
        if (it != m_meshes.end()) {
            m_meshes.erase(it);
        }
    }*/

    /*Mesh& Scene::GetMesh(const Mesh& mesh) {
        for (Mesh& m : m_meshes) {
            if (&m == &mesh) {
                return m;
            }
        }
    }*/

    std::vector<Mesh>& Scene::GetMeshes() {
        return m_meshes;
    }
}