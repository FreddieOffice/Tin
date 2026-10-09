#ifndef TIN_SCENE_MANAGER_HPP
#define TIN_SCENE_MANAGER_HPP

#include "Tin/Scene/Scene.hpp"

namespace Tin {
    class SceneManager {
    public:
        SceneManager();

        void Destroy();

        // Sets the active scene
        void SetActiveScene(std::shared_ptr<Scene> scene);
        // Returns the active scene
        std::shared_ptr<Scene> GetActiveScene() const;
    private:
        std::shared_ptr<Scene> m_activeScene = nullptr;
        //std::vector<std::shared_ptr<Scene>> m_sceneList;
    };
}

#endif