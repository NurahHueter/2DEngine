#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "CameraCmp.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "PhysicsManager.h"
namespace mmt_gd
{
    void SpaceState::init()
    {

        //map
        tson::Tileson t;
        const fs::path tileMapresourcePath = { "Assets/SpaceShip" };
        const std::unique_ptr<tson::Map> map = t.parse(tileMapresourcePath / "spaceGame.tmj");
        mapTile.loadMap(map, tileMapresourcePath);

        const auto& mapGo = std::make_shared<GameObject>("map");
        mapTile.getTiledLayer(*mapGo, map, m_window, m_RenderManager);
        mapTile.getObjectLayer(map, m_RenderManager, m_gameObjectManager);
        mapGo->init();
        m_gameObjectManager.addGameObject(mapGo);

        //set a camera on the tilemapSize


    }

    void SpaceState::exit()
    {
        m_gameObjectManager.shutdown();
        m_RenderManager.shutdown();
    }

    void SpaceState::update(float deltaTime)
    {

        PhysicsManager::instance().update();
        m_gameObjectManager.update(deltaTime);
    }

    void SpaceState::draw()
    {
        m_window.clear({ 0, 0, 255 });

        m_RenderManager.draw();


        for (auto body : PhysicsManager::instance().m_bodies)
        {
            if (std::shared_ptr<BoxCollisionCmp> tempP = body.lock())
            {
                sf::RectangleShape m_debugGeometry;
                m_debugGeometry.setPosition(tempP->m_shape.getPosition());
                m_debugGeometry.setSize(tempP->m_shape.getSize());
                m_debugGeometry.setFillColor(sf::Color::Transparent);
                m_debugGeometry.setOutlineColor(sf::Color::Red);
                m_debugGeometry.setOutlineThickness(2);

                m_window.draw(m_debugGeometry);
            }
        }
        m_window.display();
    }
}