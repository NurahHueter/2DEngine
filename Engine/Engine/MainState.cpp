#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "CameraCmp.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SpriteRenderCmp.h"
#include "MoveCmp.h"
#include "MouseMoveCmp.h"
#include "RigidBodyCmp.h"
#include "BoxCollisionCmp.h"
#include "PhysicsManager.h"
namespace mmt_gd
{
void MainState::init()
    {

    //map
    tson::Tileson t;
    const fs::path tileMapresourcePath = { "Assets" };
    const std::unique_ptr<tson::Map> map = t.parse(tileMapresourcePath / "game.tmj");
    mapTile.loadMap(map, tileMapresourcePath);

    const auto& mapObj = std::make_shared<GameObject>("map");
    mapTile.getTiledLayer(*mapObj, map, m_window, m_RenderManager);
    mapTile.getObjectLayer(map, m_RenderManager, m_gameObjectManager);
    mapObj->init();
    m_gameObjectManager.addGameObject(mapObj);

    //if (m_gameObjectManager.getGameObject("Player"))
    //{
    //    const auto& camera = std::make_shared <GameObject>("camera");
    //    const auto& cameraCmp = std::make_shared<CameraCmp>(*camera, m_window, sf::Vector2f(m_window.getSize().x, m_window.getSize().y), m_gameObjectManager.getGameObject("Player"));
    //    camera->addComponent(cameraCmp);
    //    m_RenderManager.addCompToLayer("ObjectLayer", cameraCmp);
    //    camera->init();

    //    m_gameObjectManager.addGameObject(camera);
    //    m_RenderManager.addLayer("camera", 20);
    //}

}

void MainState::exit()
{
    m_gameObjectManager.shutdown();
    PhysicsManager::instance().shutdown();
    m_RenderManager.shutdown();
}

void MainState::update(float deltaTime)
{
    PhysicsManager::instance().update();
    m_gameObjectManager.update(deltaTime);
}

void MainState::draw()
{
  m_window.clear({ 0, 0, 0 });

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