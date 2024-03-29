#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "ProjectileCmp.h"
#include "GameObject.h"
#include "HealthCmp.h"
#include "PowerUpsCmp.h"
#include "GameObjectManager.h"
#include "ProjectileIdentityCmp.h"
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

        if (const auto player = GameObjectManager::instance().getGameObject("Player"))
        {
            if (InputManager::instance().isKeyPressed("shoot", 1) && player)
            {
                player->getComponent<ProjectileCmp>()->shoot(InputManager::instance().getMousPosition());
            }
        }

       const auto coll_pairs = PhysicsManager::instance().getCollisionPairs();
       for (const auto p : coll_pairs)
        {
            if (p.first->getType() == ObjectType::Spaceship 
                && p.second->getType() == ObjectType::Spaceship)
            {
              p.first->getComponent<HealthCmp>()->getDamage();
            }
            else if(p.first->getType() == ObjectType::Spaceship 
                && p.second->getType() == Projectile 
                && (p.first->getId() != p.second->getComponent<ProjectileIdentityCmp>()->getSpaceShipId()))
            {
              p.first->getComponent<HealthCmp>()->getDamage();
            }
            else if (p.first->getType() == ObjectType::PowerUp 
                && p.second->getType() == ObjectType::Spaceship)
            {
                p.first->getComponent<PowerUpCmp>()->collect(p.second);
            }
            else if (p.first->getType() == ObjectType::Projectile)
            {
                if (p.second->getType() == ObjectType::Spaceship &&
                    (p.second->getId() == p.first->getComponent<ProjectileIdentityCmp>()->getSpaceShipId()))
                {
                }
                else
                {
                    p.first->setActive(false);
                }
            }
            else if (p.first->getType() == ObjectType::PowerUp)
            {
                p.first->getComponent<PowerUpCmp>()->respawn();
            }
        }

       //Lose and Winning Condition
        if (!GameObjectManager::instance().getGameObject("Player"))
        {
            GameStateManager::instance().setState("MenuState");
        }
        else if (GameObjectManager::instance().getObjectsByType(ObjectType::Spaceship).size() <= 1)
        {
            GameStateManager::instance().setState("MenuState");
        }
    }

    void SpaceState::draw() 
    {
        RenderManager::instance().getWindow().clear({0, 0, 0});
        RenderManager::instance().draw();

        // for (auto body : PhysicsManager::instance().m_bodies)
        // {
        //     if (std::shared_ptr<BoxCollisionCmp> tempP = body.lock())
        //     {
        //         {
        //             sf::RectangleShape m_debugGeometry;
        //             m_debugGeometry.setPosition(tempP->m_shape.getPosition());
        //             m_debugGeometry.setSize(tempP->m_shape.getSize());
        //             m_debugGeometry.setFillColor(sf::Color::Transparent);
        //             m_debugGeometry.setOutlineColor(sf::Color::Red);
        //             m_debugGeometry.setOutlineThickness(2);

        //             RenderManager::instance().getWindow().draw(m_debugGeometry);
        //         }
        //     }
        // }
        RenderManager::instance().getWindow().display();
    }
}