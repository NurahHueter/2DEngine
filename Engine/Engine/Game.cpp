//Game.cpp
#pragma once
#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "GameStateManager.h"
#include "GameState.h"


	void Game::Initialize()
	{
		InputManager::instance().bind("switch", sf::Keyboard::Key::Space,1);
		InputManager::instance().bind("music", sf::Keyboard::Key::M,1);
		InputManager::instance().bind("up", sf::Keyboard::Key::W, 1);
		InputManager::instance().bind("down", sf::Keyboard::Key::S, 1);
		InputManager::instance().bind("left", sf::Keyboard::Key::A, 1);
		InputManager::instance().bind("right", sf::Keyboard::Key::D, 1);
		InputManager::instance().bind("leftclick", sf::Mouse::Left, 2);

		GameStateManager::instance().Init();
		GameStateManager::instance().setState("MainState");	
	};

	void Game::Run() 
	{
		Initialize();

		while (m_window.isOpen())
		{
			float deltaTime = m_clock.restart().asSeconds();
			HandleEvents();
			Update(deltaTime);
			GameStateManager::instance().draw(m_window);
			//Draw();

		}
	};

	
	void Game::Update(float deltaTime)
	{

		if (InputManager::instance().isKeyDown("music",1))
		{
			if (AssetManager::instance().m_Music.find("cooleMusik") != AssetManager::instance().m_Music.end())
			{
					AssetManager::instance().m_Music["cooleMusik"]->play();
			}
			else
			{
				std::cout << "Musik wurde nicht gefunden" << std::endl;
			}
		}
		

		if (InputManager::instance().isKeyUp("switch",1))
		{
			if (m_isGameInMenu)
			{
				GameStateManager::instance().setState("MenuState");
				m_isGameInMenu = false;
			}
			else
			{
				GameStateManager::instance().setState("MainState");
				m_isGameInMenu = true;
			}	
		}

		GameStateManager::instance().update(deltaTime);
		InputManager::instance().update();

	}

	void Game::HandleEvents() 
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				
			}
			
			InputManager::instance().handleEvents(event);
			CloseGame(event.key);
		}
	};

	void Game::CloseGame(sf::Event::KeyEvent& e)
	{
		if (e.code == sf::Keyboard::Key::Escape)
		{
			m_window.close();
		}
	};


