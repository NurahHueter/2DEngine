#pragma once

#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "GameObject.h"
#include "RenderComponent.h"

void MenuState::init()
{
    /*AssetManager::instance().LoadTexture("lava", "../Assets/LavaTile.png");*/
    std::cout << "init Menu State" << std::endl;
    /*spriteLava.setTexture(*AssetManager::instance().m_Textures["lava"]);*/

    std::shared_ptr<GameObject> lava = std::make_shared<GameObject>();
    std::unique_ptr<Component> renderlava = std::make_unique<RenderComponent>("../Assets/LavaTile.png", "lava");
    lava->addComponent(renderlava);
}

void MenuState::exit()
{
    AssetManager::instance().UnloadTexture("lava");
    std::cout << "exit Menu State" << std::endl;
}

void MenuState::update(float deltaTime)
{
    std::cout << "update Menu State" << std::endl;
}

void MenuState::draw(sf::RenderWindow& m_window)
{
    std::cout << "draw Menu State" << std::endl;
    m_window.clear({ 255, 0, 255 });
    m_window.display();
}

void MainState::init()
{
    std::cout << "init Main State" << std::endl;
    AssetManager::instance().LoadTexture("crystal", "../Assets/crystal.png");
    AssetManager::instance().LoadSoundBuffer("coolerSound", "../Assets/completeSound.wav");
    AssetManager::instance().LoadMusic("cooleMusik", "../Assets/musicTrack.ogg");

    sprite.setTexture(*AssetManager::instance().m_Textures["crystal"]);
   
}

void MainState::exit()
{
    AssetManager::instance().UnloadTexture("crystal");
    AssetManager::instance().UnloadSoundBuffer("coolerSound");
    AssetManager::instance().UnloadMusic("cooleMusik");
    std::cout << "Exit Main State" << std::endl;
}

void MainState::update(float deltaTime)
{
    std::cout << "update Main State" << std::endl;
}

void MainState::draw(sf::RenderWindow& m_window)
{
    std::cout << "draw Main State" << std::endl;
    m_window.clear({ 0, 0, 255 });
    m_window.draw(sprite);
    m_window.display();
}
