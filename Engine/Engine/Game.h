#pragma once

class Game
{
public:
	void Run();
	~Game() {};
	const int m_WIDTH = 800;
	const int m_HEIGHT = 600;
	sf::VideoMode m_mode = { 800, 600 };


	Game() : m_window(m_mode, "SFML Window")
	{
		m_window.setVerticalSyncEnabled(true);
		//m_window.KeyPressed += CloseGame;		
	}

private: 
	void Initialize();
	void Update(float deltaTime);
	void HandleEvents();
	void CloseGame(sf::Event::KeyEvent& e);
	void Draw();

	sf::Sprite sprite;
	sf::Clock m_clock;
	sf::RenderWindow m_window;
	sf::Color m_bg_color = { 0, 0, 255 };
};
