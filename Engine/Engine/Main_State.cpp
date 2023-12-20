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
#include "RigidBodyCmp.h"
#include "BoxCollisionCmp.h"
#include "PhysicsManager.h"
namespace mmt_gd
{
void MainState::init()
    {
    //all AsstetsforTheState
    AssetManager::instance().LoadTexture("rocket", "../Assets/Hunter1-right.bmp");
    std::shared_ptr<sf::Texture> rocket_T = AssetManager::instance().m_Textures["rocket"];

    AssetManager::instance().LoadTexture("background", "../Assets/bg_space_seamless.png");
    std::shared_ptr<sf::Texture> background_T = AssetManager::instance().m_Textures["background"];

    assets.push_back("rocket");
    assets.push_back("background");

    //map
    tson::Tileson t;
    const std::unique_ptr<tson::Map> map = t.parse(mapTile.m_resourcePath / "game.tmj");
    mapTile.loadMap(map);

    const auto& mapObj = std::make_shared<GameObject>("map");
    mapTile.getTiledLayer(*mapObj, map, m_window);

    mapObj->init();
    m_gameObjectManager.addGameObject(mapObj);

    //rocket_one -> mit WASD
    const auto& rocket_one = std::make_shared<GameObject>("rocket_one");
    const auto& renderRocket = std::make_shared<SpriteRenderCmp>(*rocket_one, m_window, rocket_T);
    const auto& moveRocket = std::make_shared<MoveCmp>(*rocket_one, sf::Vector2f(0, 0), 500.f);
    const auto& rigidbodyRocket = std::make_shared<RigidBodyCmp>(*rocket_one);
    const auto& boxcollisionBoxRocket = std::make_shared<BoxCollisionCmp>(*rocket_one, sf::Vector2f(10.0f, 10.f), sf::Vector2f(10.0f, 10.f), rigidbodyRocket, false);

    rocket_one->addComponent(renderRocket);
    rocket_one->addComponent(moveRocket);
    rocket_one->addComponent(rigidbodyRocket);
    rocket_one->addComponent(boxcollisionBoxRocket);
    rocket_one->setPosition(sf::Vector2f(500, -5));
    rocket_one->init();

    //rocket_two -> mit Mouse
    const auto& rocket_two = std::make_shared<GameObject>("rocket_two");
    const auto& mouseMoveRocket = std::make_shared<MouseMoveCmp>(*rocket_two, sf::Vector2f(100, 0), 500.f);
    const auto& renderRocketTwo = std::make_shared<SpriteRenderCmp>(*rocket_two, m_window, rocket_T);
    const auto& rigidbodyRocketTwo = std::make_shared<RigidBodyCmp>(*rocket_two);
    const auto& boxcollisionBoxRocketTwo = std::make_shared<BoxCollisionCmp>(*rocket_two, sf::Vector2f(10.0f, 10.f), sf::Vector2f(100.0f, 100.f), rigidbodyRocketTwo, false);

    rocket_two->addComponent(renderRocketTwo);
    rocket_two->addComponent(mouseMoveRocket);
    rocket_two->addComponent(rigidbodyRocketTwo);
    rocket_two->addComponent(boxcollisionBoxRocketTwo);
    rocket_two->setPosition(sf::Vector2f(0, 0));
    rocket_two->init();

    sf::Vector2f rocketOnePosition = rocket_one->getPosition();
    sf::Vector2f rocketTwoPosition = rocket_two->getPosition();
    std::cout<< rocket_one->getPosition().x;
 

    //camera
    const auto& camera = std::make_shared<GameObject>("camera");
    //set the camera in the center of the screen, if you dont do this the 0,0 point is in the middle 
    camera->setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);

    ///set size of size from window
    const auto& cameraCmp = std::make_shared<CameraCmp>(*camera, m_window,sf::Vector2f(m_window.getSize().x, m_window.getSize().y), *rocket_one);
    camera->addComponent(cameraCmp);

    camera->init();
    rocket_one->getId();
    m_gameObjectManager.addGameObject(rocket_one);
    m_gameObjectManager.addGameObject(rocket_two);
    
    m_gameObjectManager.addGameObject(camera);

    std::cout<<m_gameObjectManager.getGameObject("rocket_one")->getPosition().x;
    m_physicsManager.init(rocketOnePosition, rocketTwoPosition);

}


void MainState::exit()
{
    m_gameObjectManager.shutdown();
    std::vector<std::string>::iterator obj;
    for (obj = assets.begin(); obj < assets.end(); obj++)
    { 
       AssetManager::instance().UnloadTexture(*obj);
    }
}

void MainState::update(float deltaTime)
{
    m_physicsManager.findCollisions(m_physicsManager.m_bodies, *m_gameObjectManager.getGameObject("rocket_one"), *m_gameObjectManager.getGameObject("rocket_two"));
    m_physicsManager.resolveCollisions(m_physicsManager.m_manifolds);
    m_gameObjectManager.update(deltaTime);
}

void MainState::draw()
{
    m_window.clear({ 0, 0, 255 });

    m_gameObjectManager.draw();

    
    for (auto& body : m_physicsManager.m_bodies)
    {
        body.m_debugGeometry.setPosition(body.m_position);
       // std::cout << body.m_position.x;
        m_window.draw(body.m_debugGeometry);
        
    }
    m_window.display();
}
}