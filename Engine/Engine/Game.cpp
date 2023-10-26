#pragma
#include "All_Includes.h"

namespace sf 
{
	void Game::Initialize()
	{
		InputManager::instance().Init(m_window);  //pointer?

		// Load Sound
		//AssetManager.LoadSound("CompleteSound", @".\Assets\completeSound.wav");

		// Load Music
		//AssetManager.LoadMusic("MusicTrack", @".\Assets\musicTrack.ogg");

		// Play Music
		//AssetManager.Music["MusicTrack"].Play();

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
		InputManager::instance().update();
	};
	void Game::HandleEvents() 
	{
		//if (event.type == sf::Event::Closed) {
		//	m_window.close();
		//}
	};
	void Game::CloseGame(const Event::KeyEvent& e)
	{
		if (e.code == Keyboard::Key::Escape)
		{
			m_window.close();
		}
	};
	void Game::Draw() 
	{
		m_window.clear(m_bg_color);

		//draw gameobject

		m_window.display();
	};
}

