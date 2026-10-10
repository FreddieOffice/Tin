#include "Tin/TinPCH.hpp"
#include "Tin/Scene/Scene.hpp"

namespace Tin {
    Scene::Scene(const std::string& name, const Shader& basicShader, const Environment& environment) : name(name), m_basicShader(basicShader), environment(environment) {}

    void Scene::Render(Renderer& renderer) {
        // Submit meshes to the renderer
        for (Mesh& mesh : m_meshes) {
            renderer.Submit(mesh, *mesh.material, mesh.transform.GetModelMatrix(), m_basicShader);
        }

        // Render the skybox last (if the sky type is skybox)
        if (environment.type == Enum::SkyType::Skybox) {
            renderer.RenderSkybox();
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

    /*std::vector<Mesh>& Scene::GetMeshes() {
        return m_meshes;
    }*/
}
