#pragma once
#include"pch.h"

struct WindowManager
{
	static
		WindowManager&
		instance()
	{
		static WindowManager w;
		return w;
	} // instance

	WindowManager(const WindowManager&) = delete;
	WindowManager& operator = (const WindowManager&) = delete;
	

	sf::RenderWindow m_window;

private:

	WindowManager()
	{
		m_window.setVerticalSyncEnabled(true);
		//m_window.KeyPressed += CloseGame;		
	}
	~WindowManager() {}

};