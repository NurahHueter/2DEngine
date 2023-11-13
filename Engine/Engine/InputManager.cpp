#pragma once
#include "pch.h"
#include "InputManager.h"


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
			std::cout << "keypressed";
			m_isKeyDown[event.key.code] = true;
			m_isKeyPressed[event.key.code] = true;
		}
		else if (event.type == sf::Event::EventType::KeyReleased)
		{
			std::cout << "keyrelesead";
			m_isKeyUp[event.key.code] = true;
			m_isKeyPressed[event.key.code] = false;
		}
			
	}
