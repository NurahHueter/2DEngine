#pragma once

#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "Background.h"
#include "Camera.h"
#include "Rocket.h"
#include "Rocket2.h"
#include "WindowManager.h"
#include "GameObject.h"

void MenuState::init()
{

}

void MenuState::exit()
{

}

void MenuState::update(float deltaTime)
{
}

void MenuState::draw(sf::RenderWindow& m_window)
{
    m_window.clear({ 255, 0, 255 });

    m_window.display();
}

void MainState::init()
{
    AssetManager::instance().LoadSoundBuffer("coolerSound", "../Assets/completeSound.wav");
    AssetManager::instance().LoadMusic("cooleMusik", "../Assets/musicTrack.ogg");
   
 //   background = std::make_shared<Background>();
 //   background->init();
 //   rocket = std::make_shared<Rocket>();
 //   rocket->init();
	//rocket2= std::make_shared<Rocket2>();
	//rocket2->init();
 //   camera = std::make_shared<Camera>(sf::Vector2f(50, 50), sf::Vector2f(WindowManager::instance().m_window.getSize().x, WindowManager::instance().m_window.getSize().y));
    std::shared_ptr<GameObject> rocket_one = std::make_shared<GameObject>();
    std::shared_ptr<RenderCmp> renderRocket = std::make_shared<RenderCmp>("RenderRocket", rocket_one, "../Assets/Hunter1-right.bmp", "rocket");
    std::shared_ptr<MoveCmp> moveRocket = std::make_shared<MoveCmp>("MoveRocket",rocket_one, sf::Vector2f(0, 0), 200.f);

    rocket_one->addComponent(std::static_pointer_cast<Component>(renderRocket));
    rocket_one->setPosition(sf::Vector2f(300, 500));

    gameObjects.insert("rocket_one", rocket_one);
}

void MainState::exit()
{
    AssetManager::instance().UnloadSoundBuffer("coolerSound");
    AssetManager::instance().UnloadMusic("cooleMusik");
    background.reset();
    rocket.reset();
	rocket2.reset();
}

void MainState::update(float deltaTime)
{
    
    //camera->move(sf::Vector2f(50.0f* deltaTime, 0.f));
  
    //background->swap(camera->getPosition().x);

    if (InputManager::instance().isKeyPressed("up", 1))
    {
        moveComponent->setDirection(moveComponent->getDirection() + sf::Vector2f(0, -1));
    }
    if (InputManager::instance().isKeyPressed("down", 1))
    {
        moveComponent->setDirection(moveComponent->getDirection() + sf::Vector2f(0, 1));
    }
    if (InputManager::instance().isKeyPressed("left", 1))
    {
        moveComponent->setDirection(moveComponent->getDirection() + sf::Vector2f(-1, 0));
    }
    if (InputManager::instance().isKeyPressed("right", 1))
    {
        moveComponent->setDirection(moveComponent->getDirection() + sf::Vector2f(1, 0));
    }
    
    rocket_one->update(deltaTime);

    //if (rocket->getPosition().x <= camera->getPosition().x)
    //{
    //    rocket->setPosition(camera->getPosition().x, rocket->getPosition().y);
    //}
    //if (rocket2->getPosition().x <= camera->getPosition().x)
    //{
    //    rocket2->setPosition(camera->getPosition().x, rocket2->getPosition().y);
    //}
}

void MainState::draw(sf::RenderWindow& m_window)
{
    m_window.clear({ 0, 0, 255 });
    background->draw(m_window);
   
    rocket->draw(m_window);
	rocket2->draw(m_window);
    camera->draw(m_window);
    m_window.display();
}
