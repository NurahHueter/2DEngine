	#pragma once
	#include "InputManager.h"


	namespace sf {

		void InputManager::Init(Window& window)
		{
			window.setKeyRepeatEnabled(false);
		
			sf::Event event;
			while (window.pollEvent(event)) {
				handleEvents(event);
			}

			m_isKeyDown[(Keyboard::Key::W)] = false;
			m_isKeyDown[(Keyboard::Key::A)] = false;		
			m_isKeyDown[(Keyboard::Key::S)] = false;
			m_isKeyDown[(Keyboard::Key::D)] = false;
			m_isKeyDown[(Keyboard::Key::Escape)] = false;

			m_isKeyUp[(Keyboard::Key::W)] = false;
			m_isKeyUp[(Keyboard::Key::A)] = false;
			m_isKeyUp[(Keyboard::Key::S)] = false;
			m_isKeyUp[(Keyboard::Key::D)] = false;
			m_isKeyUp[(Keyboard::Key::Escape)] = false;
		
			m_isKeyPressed[(Keyboard::Key::W)] = false;
			m_isKeyPressed[(Keyboard::Key::A)] = false;
			m_isKeyPressed[(Keyboard::Key::S)] = false;
			m_isKeyPressed[(Keyboard::Key::D)] = false;
			m_isKeyPressed[(Keyboard::Key::Escape)] = false;
		};


		void InputManager::update()
		{
			for (auto& kv : m_isKeyDown)
			{
				m_isKeyDown[kv.first] = false;
				//kv.second = false;
			}
			for (auto& kv : m_isKeyUp) 
			{
				m_isKeyUp[kv.first] = false;
			}
		};

		bool InputManager::GetKeyPressed(Keyboard::Key key)
		{
			return m_isKeyPressed.find(key) != m_isKeyPressed.end() ? m_isKeyPressed[key] : false;
		};

		bool InputManager::GetKeyDown(Keyboard::Key key)
		{
			return m_isKeyDown.find(key) != m_isKeyDown.end() ? m_isKeyDown[key] : false;
		};
		bool InputManager::GetKeyUp(Keyboard::Key key)
		{
			return m_isKeyUp.find(key) != m_isKeyUp.end() ? m_isKeyUp[key] : false;
		};


		//void InputManager::OnKeyPressed(const Event::KeyEvent& e)
		//{
		//	if (m_isKeyPressed.find(e.code) != m_isKeyPressed.end())
		//	{
		//		m_isKeyDown[e.code] = true;
		//		m_isKeyPressed[e.code] = true;
		//	}
		//};

		//void InputManager::OnKeyReleased(const Event::KeyEvent& e)
		//{
		//	if (m_isKeyPressed.find(e.code) != m_isKeyPressed.end())
		//	{
		//		m_isKeyUp[e.code] = true;
		//		m_isKeyPressed[e.code] = false;
		//	}
		//}
		void InputManager::handleEvents(sf::Event& event)
		{
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				m_isKeyDown[event.key.code] = true;
				m_isKeyPressed[event.key.code] = true;
			}
			else if (event.type == sf::Event::EventType::KeyReleased)
			{
				m_isKeyUp[event.key.code] = true;
				m_isKeyPressed[event.key.code] = false;
			}

		}

	}