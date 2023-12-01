#pragma once

#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "Background.h"
#include "Camera.h"
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

    //rocket
    std::shared_ptr<GameObject> rocket_one = std::make_shared<GameObject>();
    std::shared_ptr<RenderCmp> renderRocket = std::make_shared<RenderCmp>("RenderRocket", rocket_one, "../Assets/Hunter1-right.bmp", "rocket");
    std::shared_ptr<MoveCmp> moveRocket = std::make_shared<MoveCmp>("MoveRocket", rocket_one, sf::Vector2f(0, 0), 200.f);

    rocket_one->addComponent("RenderRocket" ,std::dynamic_pointer_cast<Component>(renderRocket));
    rocket_one->addComponent("MoveRocket",std::dynamic_pointer_cast<Component>(moveRocket));
    rocket_one->setPosition(sf::Vector2f(300, 500));

    //background
    std::shared_ptr<GameObject> background_one = std::make_shared<GameObject>();
    std::shared_ptr<GameObject> background_two = std::make_shared<GameObject>();

    std::shared_ptr<RenderCmp> render_background_one = std::make_shared<RenderCmp>("RenderSpace", background_one, "../Assets/bg_space_seamless.png", "Space");
    std::shared_ptr<RenderCmp> render_background_two = std::make_shared<RenderCmp>("RenderSpace2", background_one, "../Assets/bg_space_seamless.png", "Space2");

    background_one->addComponent("background_one", std::dynamic_pointer_cast<Component>(render_background_one));
    background_two->addComponent("background_two", std::dynamic_pointer_cast<Component>(render_background_two));

    //set position of second background after the first
    float width_texture = 0;
    auto it = background_one->components.find("background_one");
    if (it != background_one->components.end()) {
        if (auto temp = std::dynamic_pointer_cast<RenderCmp>(it->second))
        {
            width_texture = temp->sprite->getTextureRect().width;
        }
    }
    background_two->setPosition(sf::Vector2f(background_one->getPosition().x + width_texture, background_one->getPosition().y));

    //add to map
    gameObjects.insert(std::make_pair("rocket_one", rocket_one));
    gameObjects.insert(std::make_pair("background_one", background_one));
    gameObjects.insert(std::make_pair("background_two", background_two));
}


void MainState::exit()
{
    AssetManager::instance().UnloadSoundBuffer("coolerSound");
    AssetManager::instance().UnloadMusic("cooleMusik");

    //TODO: Assets in RenderCMP unloaden
}

void MainState::update(float deltaTime)
{
    
    //camera->move(sf::Vector2f(50.0f* deltaTime, 0.f));
  
    //background->swap(camera->getPosition().x);

    
    for (auto& obj : gameObjects) {
        obj.second->update(deltaTime);
    }

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

    for (auto& obj : gameObjects) {
        obj.second->draw(m_window);
    }

    m_window.display();
}
