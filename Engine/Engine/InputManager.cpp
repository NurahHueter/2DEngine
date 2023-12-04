#pragma once
#include "pch.h"
#include "InputManager.h"
#include "WindowManager.h"


	void InputManager::update()
	{
		for (auto& kv : m_isKeyDown)
		{
			m_isKeyDown[kv.first] = false;
		}
		for (auto& kv : m_isKeyUp)
		{
			m_isKeyUp[kv.first] = false;
		}
		for (auto& kv : m_isMouseDown)
		{
			m_isMouseDown[kv.first] = false;
		}
		for (auto& kv : m_isMouseUp)
		{
			m_isMouseUp[kv.first] = false;
		}
	};

	bool InputManager::isKeyDown(int keyCode)
	{
		return m_isKeyDown.find(keyCode) != m_isKeyDown.end() ? m_isKeyDown[keyCode] : false;
	};

	bool InputManager::isKeyUp(int keyCode)
	{
		return m_isKeyUp.find(keyCode) != m_isKeyUp.end() ? m_isKeyUp[keyCode] : false;
	};
	bool InputManager::isKeyPressed(int keyCode)
	{
		return m_isKeyPressed.find(keyCode) != m_isKeyPressed.end() ? m_isKeyPressed[keyCode] : false;
	};


	bool InputManager::isKeyDown(const std::string& action)					
	{
		if (m_bindings.find(action) != m_bindings.end())				//Checken, ob ein binding im Dict ist
		{
			int keyCode = m_bindings[action];
			return isKeyDown(keyCode);									// wenn ja, dann isKeyDown mit dem keyCode aufrufen
		}

		return false;
	};

	bool InputManager::isKeyUp(const std::string& action)
	{
		if (m_bindings.find(action) != m_bindings.end())	
		{
			int keyCode = m_bindings[action];
			return isKeyUp(keyCode);
		}

		return false;
	};
	bool InputManager::isKeyPressed(const std::string& action)
	{
		if (m_bindings.find(action) != m_bindings.end())
		{
			int keyCode = m_bindings[action];
			return isKeyPressed(keyCode);
		}

		return false;
	};

	//MouseInput
	bool InputManager::isMouseDown(int keyCode)
	{
		return m_isMouseDown.find(keyCode) != m_isMouseDown.end() ? m_isMouseDown[keyCode] : false;
	};

	bool InputManager::isMouseUp(int keyCode)
	{
		return m_isMouseUp.find(keyCode) != m_isMouseUp.end() ? m_isMouseUp[keyCode] : false;
	};
	bool InputManager::isMousePressed(int keyCode)
	{
		return m_isMousePressed.find(keyCode) != m_isMousePressed.end() ? m_isMousePressed[keyCode] : false;
	};


	bool InputManager::isMouseDown(const std::string& action, int playerIdx)
	{
		if (m_bindings.find(action) != m_bindings.end()) // Überprüfen, ob "action" im Dictionary vorhanden ist
		{
			auto binding = m_bindings[action]; // `binding` enthält die BindingForPlayer-Klasse
			return isMouseDown(binding.keyCode) && binding.playerIdx == playerIdx; // Wenn ja, dann rufe isKeyDown mit dem KeyCode auf und überprüfe, ob der playerIdx übereinstimmt
		}

		return false;
	};

	bool InputManager::isMouseUp(const std::string& action, int playerIdx)
	{
		if (m_bindings.find(action) != m_bindings.end())
		{
			auto binding = m_bindings[action];
			return isMouseUp(binding.keyCode) && binding.playerIdx == playerIdx;
		}

		return false;
	};
	bool InputManager::isMousePressed(const std::string& action, int playerIdx)
	{
		if (m_bindings.find(action) != m_bindings.end())
		{
			auto binding = m_bindings[action];
			return isMousePressed(binding.keyCode) && binding.playerIdx == playerIdx;
		}

		return false;
	};


	void InputManager::bind(const std::string& name, int keyCode)
	{
		m_bindings[name] = keyCode;
	};

	void InputManager::unbind(const std::string& name)
	{
		auto binding_iterator = m_bindings.find(name);					//wenn es drin ist, dann ist binding iterator ein Iterator der auf den wert zeigt, sonst zeigt er ans ende der map
		if (binding_iterator != m_bindings.end())						
		{
			m_bindings.erase(binding_iterator);
		}	
	};


	void InputManager::handleEvents(sf::Event& event)
	{
		if (event.type == sf::Event::EventType::KeyPressed)
		{
			m_isKeyDown[event.key.code] = true;
			m_isKeyPressed[event.key.code] = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased)
		{
			m_isKeyUp[event.key.code] = true;
			m_isKeyPressed[event.key.code] = false;
		}
		if (event.type == sf::Event::EventType::MouseButtonPressed)
		{
				m_isMouseDown[event.key.code] = true;
				m_isMousePressed[event.key.code] = true;
		}
		if (event.type == sf::Event::EventType::MouseButtonReleased)
		{
			m_isMouseUp[event.key.code] = true;
			m_isMousePressed[event.key.code] = false;
		}
	}


	sf::Vector2f InputManager::getMousPosition()
	{
		sf::Vector2f worldMousePosition = WindowManager::instance().m_window.mapPixelToCoords(sf::Mouse::getPosition(WindowManager::instance().m_window));
		return worldMousePosition;
	}
