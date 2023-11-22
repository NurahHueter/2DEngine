#pragma once

#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "Background.h"
#include "Camera.h"
#include "Rocket.h"
#include "Rocket2.h"
#include "WindowManager.h"

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
   
    background = std::make_shared<Background>();
    background->init();
    rocket = std::make_shared<Rocket>();
    rocket->init();
	rocket2= std::make_shared<Rocket2>();
	rocket2->init();
    camera = std::make_shared<Camera>(sf::Vector2f(50, 50), sf::Vector2f(WindowManager::instance().m_window.getSize().x, WindowManager::instance().m_window.getSize().y));
    
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
 
    camera->move(sf::Vector2f(50.0f* deltaTime, 0.f));
  
    background->swap(camera->getPosition().x);
    
    rocket->update(deltaTime);
	rocket2->update(deltaTime);

    if (rocket->getPosition().x <= camera->getPosition().x)
    {
        rocket->setPosition(camera->getPosition().x, rocket->getPosition().y);
    }
    if (rocket2->getPosition().x <= camera->getPosition().x)
    {
        rocket2->setPosition(camera->getPosition().x, rocket2->getPosition().y);
    }
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
