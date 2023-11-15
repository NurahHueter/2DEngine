// Game.h

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
	sf::Color m_bg_color = { 0, 0, 255 };
    sf::RenderWindow m_window;

private: 
	void Initialize();
	void Update(float deltaTime);
	void HandleEvents();
	void CloseGame(sf::Event::KeyEvent& e);
	//void Draw();

	sf::Clock m_clock;
	
	bool m_isGameInMenu = true;	
};
