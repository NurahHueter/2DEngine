//MainState gitbs scho laut vc idk wie man des wegmacht

#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "CameraCmp.h"
#include "WindowManager.h"
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
    AssetManager::instance().LoadTexture("rocket", "../Assets/Hunter1-right.bmp");
    std::shared_ptr<sf::Texture> rocket_T = AssetManager::instance().m_Textures["rocket"];

    AssetManager::instance().LoadTexture("background", "../Assets/bg_space_seamless.png");
    std::shared_ptr<sf::Texture> background_T = AssetManager::instance().m_Textures["background"];

    assets.push_back("rocket");
    assets.push_back("background");

    const auto& map = std::make_shared<GameObject>("map");

    //rocket_one -> mit WASD
    const auto& rocket_one = std::make_shared<GameObject>("rocket_one");
    const auto& renderRocket = std::make_shared<SpriteRenderCmp>(*rocket_one, WindowManager::instance().m_window, rocket_T);
    const auto& moveRocket = std::make_shared<MoveCmp>(*rocket_one, sf::Vector2f(0, 0), 500.f);
    rocket_one->addComponent(renderRocket);
    rocket_one->addComponent(moveRocket);
    rocket_one->setPosition(sf::Vector2f(22, -5));

    rocket_one->init();

    //rocket_two -> mit Mouse
    const auto& rocket_two = std::make_shared<GameObject>("rocket_two");
    const auto& mouseMoveRocket = std::make_shared<MouseMoveCmp>(*rocket_two, sf::Vector2f(0, 0), 500.f);
    const auto& renderRocketTwo = std::make_shared<SpriteRenderCmp>(*rocket_two, WindowManager::instance().m_window, rocket_T);
    rocket_two->addComponent(renderRocketTwo);
    rocket_two->addComponent(mouseMoveRocket);
    rocket_two->setPosition(sf::Vector2f(30, -5));

    rocket_two->init();

    //camera
    const auto& camera = std::make_shared<GameObject>("camera");
    //set the camera in the center of the screen, if you dont do this the 0,0 point is in the middle 
    camera->setPosition(WindowManager::instance().m_window.getSize().x / 2, WindowManager::instance().m_window.getSize().y / 2);

    ///set size of size from window
    const auto& cameraCmp = std::make_shared<CameraCmp>(*camera, WindowManager::instance().m_window,sf::Vector2f(WindowManager::instance().m_window.getSize().x, WindowManager::instance().m_window.getSize().y), *rocket_one);
    camera->addComponent(cameraCmp);

    camera->init();

    m_gameObjectManager.addGameObject(rocket_one);
    m_gameObjectManager.addGameObject(rocket_two);
    m_gameObjectManager.addGameObject(camera);

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
    m_gameObjectManager.update(deltaTime);
}

void MainState::draw(sf::RenderWindow& m_window)
{
    m_window.clear({ 0, 0, 255 });

    m_gameObjectManager.draw();

    m_window.display();
}
}