// Game.h

#pragma once
namespace mmt_gd
{
	class Game
	{
	public:
		void Run();
		sf::Color m_bg_color = { 0, 0, 255 };

	private:
		void Initialize();
		void Update(float deltaTime);
		void HandleEvents();
		void CloseGame(sf::Event::KeyEvent& e);

		sf::Clock m_clock;
		bool m_isGameInMenu = true;
	};
}