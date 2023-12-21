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
    //all AsstetsforTheState
    //AssetManager::instance().LoadTexture("rocket", "../Engine/Assets/Hunter1-right.bmp");
    //std::shared_ptr<sf::Texture> rocket_T = AssetManager::instance().m_Textures["rocket"];

    //assets.push_back("rocket");

    //m_RenderManager.addLayer("ObjectLayer", 5);

    //map
    tson::Tileson t;
    const std::unique_ptr<tson::Map> map = t.parse(mapTile.m_resourcePath / "game.tmj");
    mapTile.loadMap(map);

    const auto& mapObj = std::make_shared<GameObject>("map");
    mapTile.getTiledLayer(*mapObj, map, m_window, m_RenderManager);
    mapTile.getObjectLayer(map, m_RenderManager, m_gameObjectManager);
    mapObj->init();
    m_gameObjectManager.addGameObject(mapObj);

    //rocket_one -> mit WASD
    //const auto& rocket_one = std::make_shared<GameObject>("rocket_one");
    //const auto& renderRocket = std::make_shared<SpriteRenderCmp>(*rocket_one, m_window, rocket_T);
    //m_RenderManager.addCompToLayer("ObjectLayer", renderRocket);
    //const auto& moveRocket = std::make_shared<MoveCmp>(*rocket_one, 500.f);
    //rocket_one->addComponent(renderRocket);
    //rocket_one->addComponent(moveRocket);
    //rocket_one->setPosition(sf::Vector2f(22, -5));

    //rocket_one->init();

    //rocket_two -> mit Mouse
    //const auto& rocket_two = std::make_shared<GameObject>("rocket_two");
    //const auto& mouseMoveRocket = std::make_shared<MouseMoveCmp>(*rocket_two, sf::Vector2f(0, 0), 500.f);
    //const auto& renderRocketTwo = std::make_shared<SpriteRenderCmp>(*rocket_two, m_window, rocket_T);
    //m_RenderManager.addCompToLayer("ObjectLayer", renderRocketTwo);
    //rocket_two->addComponent(renderRocketTwo);
    //rocket_two->addComponent(mouseMoveRocket);
    //rocket_two->setPosition(sf::Vector2f(30, -5));

    //rocket_two->init();

    ////camera
    //const auto& camera = std::make_shared<GameObject>("camera");
    ////set the camera in the center of the screen, if you dont do this the 0,0 point is in the middle 
    //camera->setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);

    /////set size of size from window
    //const auto& cameraCmp = std::make_shared<CameraCmp>(*camera, m_window,sf::Vector2f(m_window.getSize().x, m_window.getSize().y), *rocket_one);

    //camera->addComponent(cameraCmp);
    //m_RenderManager.addCompToLayer("ObjectLayer", cameraCmp);
    //camera->init();

    //m_gameObjectManager.addGameObject(rocket_one);
    //m_gameObjectManager.addGameObject(rocket_two);
    //m_gameObjectManager.addGameObject(camera);
}

void MainState::exit()
{
    m_gameObjectManager.shutdown();
    m_RenderManager.shutdown();
    std::vector<std::string>::iterator obj;
    for (obj = assets.begin(); obj < assets.end(); obj++)
    { 
       AssetManager::instance().UnloadTexture(*obj);
    }
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