// Game.h
#pragma once
#include "FPS.h"
namespace mmt_gd
{
	class Game
	{
	public:
		void Run();

	private:
		void Initialize();
		void Update(float deltaTime);
		void HandleEvents();
		void CloseGame(sf::Event::KeyEvent& e);


		sf::Clock m_clock;
		sf::RenderWindow m_window;
		Fps m_fps;
		bool m_isGameInMenu = true;
	};
}