#pragma once
#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "AssetManager.h"

	void Game::Initialize()
	{
	
		InputManager::instance().Init(m_window);  //pointer?
		AssetManager& assetManager = AssetManager::instance();

		assetManager.LoadTexture("crystal", "../Assets/crystal.png");
		assetManager.LoadSoundBuffer("coolerSound", "../Assets/completeSound.wav");
		assetManager.LoadMusic("cooleMusik", "../Assets/musicTrack.ogg");
		
		sprite.setTexture(*assetManager.m_Textures["crystal"]);
	};


	void Game::Run() 
	{
		Initialize();

		while (m_window.isOpen())
		{
			float deltaTime = m_clock.restart().asSeconds();
			HandleEvents();
			Update(deltaTime);
			Draw();
		}
	};

	void Game::Update(float deltaTime)
	{
		//foreach(var gameObject in gameObjects)
			//gameObject.Update(deltaTime);
	
		// InputManager Update
		
		if (InputManager::instance().GetKeyDown(sf::Keyboard::Key::W))
		{
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
			AssetManager::instance().m_Music["cooleMusik"]->play();
		};

		
		InputManager::instance().update();

		
	};
	void Game::HandleEvents() 
	{

		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
			CloseGame(event.key);
			InputManager::instance().handleEvents(event);
		}
	};
	void Game::CloseGame(sf::Event::KeyEvent& e)
	{
		if (e.code == sf::Keyboard::Key::Escape)
		{
			m_window.close();
		}
	};
	void Game::Draw() 
	{
		m_window.clear(m_bg_color);

		//draw gameobject
		m_window.draw(sprite);
		m_window.display();
	};


