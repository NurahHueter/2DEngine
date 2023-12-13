#include "pch.h"
#include "GameObjectManager.h"
namespace mmt_gd
#include "Debug.h"

void GameObjectManager::init()
{
    void GameObjectManager::init()
    {
    }

    void GameObjectManager::shutdown()
    {
        m_gameObjects.clear();
    }

    void GameObjectManager::update(const float deltaTime)
    {
        std::vector<GameObject::Ptr> gameObjectsToDelete{};

        for (const auto& goPair : getGameObjects())
        {
            if (goPair.second->isMarkedForDelete())
            {
                gameObjectsToDelete.push_back(goPair.second);
            }
            else if (goPair.second->isActive())
            {
                goPair.second->update(deltaTime);
            }
        }
        for (const auto& go : gameObjectsToDelete)
        {
            removeGameObject(go);
        }
    }

    void GameObjectManager::draw()
    {
        for (const auto& goPair : getGameObjects())
        {
            goPair.second->draw();
        }
    }

    void GameObjectManager::addGameObject(const GameObject::Ptr& gameObject)
    {
        if (m_gameObjects.find(gameObject->getId()) == m_gameObjects.end())
        {
            std::cout << "Game object with this m_id already exists " << gameObject->getId() << std::endl;
            m_gameObjects[gameObject->getId()] = gameObject;
        }

void GameObjectManager::addGameObject(const GameObject::Ptr& gameObject)
{
    ffAssertMsg(m_gameObjects.find(gameObject->getId()) == m_gameObjects.end(),
        "Game object with this m_id already exists " + gameObject->getId())

        m_gameObjects[gameObject->getId()] = gameObject;
     
}

    GameObject::Ptr GameObjectManager::getGameObject(const std::string& id) const
    {
        ffErrorMsg("Could not find gameobject with m_id " + id) return nullptr;
    }

    void GameObjectManager::removeGameObject(const std::shared_ptr<GameObject>& go)
    {
        if (m_gameObjects.find(go->getId()) != m_gameObjects.end())
        {
            m_gameObjects.erase(go->getId());
        }
    }
}