#pragma once
#include "All_Includes.h"
namespace sf {
class Game
{
public:
	void Run();
	const int m_WIDTH = 640;
	const int m_HEIGHT = 480;

	Game() : m_window(m_mode, "SFML Window")
	{

		m_window.setVerticalSyncEnabled(true);

		// m_window.KeyPressed += CloseGame;		benötigt KeyPressed
	}

private: 
	void Initialize();
	void Update(float deltaTime);
	void HandleEvents();
	void CloseGame(const Event::KeyEvent& e);
	void Draw();
	
	~Game() {}
	Clock m_clock;
	RenderWindow m_window;
	VideoMode m_mode = { m_WIDTH, m_HEIGHT };
	Color m_bg_color = { 0, 0, 255 };
};
}