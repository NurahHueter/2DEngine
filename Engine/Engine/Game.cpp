//Game.cpp
#pragma once
#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "GameStateManager.h"
#include "GameState.h"

namespace mmt_gd
{

	void Game::Initialize()
	{
		m_window.setVerticalSyncEnabled(true);
		m_window.create({ 800, 600 }, "SFML Window");
		InputManager::instance().setWindow(m_window);

		InputManager::instance().bind("switch", sf::Keyboard::Key::Space, 1);
		InputManager::instance().bind("music", sf::Keyboard::Key::M, 1);
		InputManager::instance().bind("up", sf::Keyboard::Key::W, 1);
		InputManager::instance().bind("down", sf::Keyboard::Key::S, 1);
		InputManager::instance().bind("left", sf::Keyboard::Key::A, 1);
		InputManager::instance().bind("right", sf::Keyboard::Key::D, 1);
		InputManager::instance().bind("shoot", sf::Keyboard::Key::R, 1);
		InputManager::instance().bind("leftclick", sf::Mouse::Left, 2);
		InputManager::instance().bind("debugdraw", sf::Keyboard::Key::Num0, 1);

		auto menu = std::make_shared<MenuState>(m_window);
		auto main = std::make_shared<MainState>(m_window);

		GameStateManager::instance().addState("MainState", main);
		GameStateManager::instance().addState("MenuState", menu);
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
			GameStateManager::instance().draw();
		}
	};


	void Game::Update(float deltaTime)
	{
		if (InputManager::instance().isKeyUp("switch", 1))
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

		std::ostringstream ss;
		m_fps.update();
		ss << " | FPS: " << m_fps.getFps();

		m_window.setTitle(ss.str());
	}

	void Game::HandleEvents()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				GameStateManager::instance().CloseGame();
				Game::~Game();
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
			GameStateManager::instance().CloseGame();
			m_window.close();
			Game::~Game();
		}
	};
}

