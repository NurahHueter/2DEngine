//MainState gitbs scho laut vc idk wie man des wegmacht

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
namespace mmt_gd
{
void MainState::init()
    {

    //map
    tson::Tileson t;
    const std::unique_ptr<tson::Map> map = t.parse(mapTile.m_resourcePath / "game.tmj");
    mapTile.loadMap(map);

    const auto& mapObj = std::make_shared<GameObject>("map");
    mapTile.getTiledLayer(*mapObj, map, m_window, m_RenderManager);
    mapTile.getObjectLayer(map, m_RenderManager, m_gameObjectManager);
    mapObj->init();
    m_gameObjectManager.addGameObject(mapObj);


    //camera
    const auto& camera = std::make_shared<GameObject>("camera");
    //set the camera in the center of the screen, if you dont do this the 0,0 point is in the middle 
    camera->setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);

    ///set size of size from window

    if (m_gameObjectManager.getGameObject("Player"))
    {
        const auto& cameraCmp = std::make_shared<CameraCmp>(*camera, m_window, sf::Vector2f(m_window.getSize().x, m_window.getSize().y), m_gameObjectManager.getGameObject("Player"));
        camera->addComponent(cameraCmp);
        m_RenderManager.addCompToLayer("ObjectLayer", cameraCmp);
        camera->init();

        m_gameObjectManager.addGameObject(camera);
        m_RenderManager.addLayer("camera", 20);
    }

}

void MainState::exit()
{
    m_gameObjectManager.shutdown();
    m_RenderManager.shutdown();
}

void MainState::update(float deltaTime)
{
    m_gameObjectManager.update(deltaTime);
}

void MainState::draw()
{
    m_window.clear({ 0, 0, 255 });

    m_RenderManager.draw();

    m_window.display();
}
}