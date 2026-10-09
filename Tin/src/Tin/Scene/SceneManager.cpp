#include "Tin/TinPCH.hpp"
#include "Tin/Scene/SceneManager.hpp"

namespace Tin {
    SceneManager::SceneManager() {

    }

    void SceneManager::Destroy() {
        m_activeScene->Destroy();
    }

    void SceneManager::SetActiveScene(std::shared_ptr<Scene> scene) {
        m_activeScene = std::move(scene);
    }

    std::shared_ptr<Scene> SceneManager::GetActiveScene() const {
        return m_activeScene;
    }
}