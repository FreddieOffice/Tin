#include "Tin/TinPCH.hpp"
#include "Tin/Scene/Scene.hpp"

namespace Tin {
    Scene::Scene(const Shader& basicShader, const Environment& environment) : m_basicShader(basicShader), environment(environment) {}

    void Scene::Render(Renderer& renderer, Camera& camera) {
        // Render meshes
        for (Mesh& mesh : m_meshes) {
            mesh.Render();
        }

        // Update camera
        camera.UpdateMatrix(m_basicShader, camera.GetProjectionMatrix(), camera.GetViewMatrix());

        // Render the skybox last (if the sky type is skybox)
        if (environment.type == Enum::SkyType::Skybox) {
            renderer.RenderSkybox(camera);
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