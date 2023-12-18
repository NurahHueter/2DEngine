#pragma once
#include <string>
#include <unordered_map>
#include "GameObject.h"
namespace mmt_gd
{
    class GameObjectManager
    {
    public:
        using GameObjectMap = std::map<std::string, GameObject::Ptr>;

        static void     init();
        void            shutdown();
        void            update(float deltaTime);
        void            addGameObject(const GameObject::Ptr& gameObject);
        GameObject::Ptr getGameObject(const std::string& id) const;

        GameObjectMap& getGameObjects()
        {
            return m_gameObjects;
        }

        void removeGameObject(const std::shared_ptr<GameObject>& go);

    private:
        GameObjectMap m_gameObjects;
    };
}