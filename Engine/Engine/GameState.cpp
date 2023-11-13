#pragma once

#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "Background.h"

void MenuState::init()
{
    /*AssetManager::instance().LoadTexture("lava", "../Assets/LavaTile.png");*/
    std::cout << "init Menu State" << std::endl;
    /*spriteLava.setTexture(*AssetManager::instance().m_Textures["lava"]);*/

    background = std::make_shared<Background>();
    background->init();
}

void MenuState::exit()
{
    std::cout << "exit Menu State" << std::endl;
    background.reset();
}

void MenuState::update(float deltaTime)
{
    std::cout << "update Menu State" << std::endl;

}

void MenuState::draw(sf::RenderWindow& m_window)
{
    std::cout << "draw Menu State" << std::endl;
    m_window.clear({ 255, 0, 255 });
    background->draw(m_window);
    m_window.display();
}

void MainState::init()
{
    std::cout << "init Main State" << std::endl;
    AssetManager::instance().LoadSoundBuffer("coolerSound", "../Assets/completeSound.wav");
    AssetManager::instance().LoadMusic("cooleMusik", "../Assets/musicTrack.ogg");
   
    background = std::make_shared<Background>();
    background->init();
}

void MainState::exit()
{
    AssetManager::instance().UnloadSoundBuffer("coolerSound");
    AssetManager::instance().UnloadMusic("cooleMusik");
    background.reset();
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
    background->draw(m_window);
    m_window.display();
}
