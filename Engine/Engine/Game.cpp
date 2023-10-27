#pragma
#include "All_Includes.h"

	void Game::Initialize()
	{
	
		sf::InputManager::instance().Init(m_window);  //pointer?
		AssetManager& assetManager = AssetManager::instance();

		std::string asset_path_texture = "../Assets/crystal.png";
		std::string asset_path_sound = "../Assets/completeSound.wav";
		std::string asset_path_music = "../Assets/musicTrack.ogg";
		std::string crystal = "crystal";
		std::string name_sound = "coolerSound";
		std::string name_music = "cooleMusik";
		assetManager.LoadTexture(crystal, asset_path_texture);
		assetManager.LoadSoundBuffer(name_sound, asset_path_sound);
		assetManager.LoadMusic(name_music, asset_path_music);
		
		test.setTexture(assetManager.m_Textures[crystal]);
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
		
		if (sf::InputManager::instance().GetKeyDown(sf::Keyboard::Key::W))
		{
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
			AssetManager::instance().m_Music["cooleMusik"]->play();
		};

		
		sf::InputManager::instance().update();

		
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
			sf::InputManager::instance().handleEvents(event);
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
		m_window.draw(test);
		m_window.display();
	};


