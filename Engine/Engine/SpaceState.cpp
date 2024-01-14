#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "CameraCmp.h"
#include "GameObject.h"
#include "HealthCmp.h"
#include "PowerUpsCmp.h"
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
        mapTile.getTiledLayer(*mapGo, map);
        mapTile.getObjectLayer(map);
        mapGo->init();

        GameObjectManager::instance().addGameObject(mapGo);

    }

    void SpaceState::exit()
    {
        GameObjectManager::instance().shutdown();
        RenderManager::instance().shutdown();
    }

    void SpaceState::update(float deltaTime)
    {
        PhysicsManager::instance().update();
        GameObjectManager::instance().update(deltaTime);

        const auto coll_pairs = PhysicsManager::instance().getCollisionPairs();
       /* for (const auto p : coll_pairs)
        {
            if (p.first->getType() == ObjectType::Spaceship && (p.second->getType() == ObjectType::Spaceship || p.second->getType() == ObjectType::Projectile))
            {
                //p.first->getComponent<HealthCmp>()->getDamage();
            }
            else if (p.first->getType() == ObjectType::PowerUp && p.second->getType() == ObjectType::Spaceship)
            {
                p.first->getComponent<PowerUpCmp>()->collect(p.second);
            }
            else if (p.first->getType() == ObjectType::Projectile)
            {
                p.first->setActive(false);
            }
        }*/
    }

    void SpaceState::draw() 
    {
        RenderManager::instance().getWindow().clear({0, 0, 0});
        RenderManager::instance().draw();

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

                RenderManager::instance().getWindow().draw(m_debugGeometry);
            }
        }
        RenderManager::instance().getWindow().display();
    }
}