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
    if (setCamera)
    {
        camera->move(sf::Vector2f(0.3f, 0.f));
        background->swap(camera->getPosition().x);
    }
    rocket->update(deltaTime);
	rocket2->update(deltaTime);
}

void MainState::draw(sf::RenderWindow& m_window)
{
    m_window.clear({ 0, 0, 255 });
    background->draw(m_window);
    if (!setCamera)
    {
        camera = std::make_shared<Camera>(sf::Vector2f(50, 50),sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
        setCamera = true;
    }
    rocket->draw(m_window);
	rocket2->draw(m_window);
    camera->draw(m_window);
    m_window.display();
}
