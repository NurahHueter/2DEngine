// Game.h

#pragma once

class Game
{
public:
	void Run();
	~Game() {};

	Game() 
	{
		//m_window.setVerticalSyncEnabled(true);
		//m_window.KeyPressed += CloseGame;		
	}
	sf::Color m_bg_color = { 0, 0, 255 };

private: 
	void Initialize();
	void Update(float deltaTime);
	void HandleEvents();
	void CloseGame(sf::Event::KeyEvent& e);
	//void Draw();

	sf::Clock m_clock;
	
	bool m_isGameInMenu = true;	
};
