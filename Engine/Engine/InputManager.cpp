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


	bool InputManager::isKeyDown(const std::string& action, int playerIdx)
	{
		if (m_bindings.find(action) != m_bindings.end()) // Überprüfen, ob "action" im Dictionary vorhanden ist
		{
			auto binding = m_bindings[action]; // `binding` enthält die BindingForPlayer-Klasse
			return isKeyDown(binding.keyCode) && binding.playerIdx == playerIdx; // Wenn ja, dann rufe isKeyDown mit dem KeyCode auf und überprüfe, ob der playerIdx übereinstimmt
		}

		return false;
	};

	bool InputManager::isKeyUp(const std::string& action, int playerIdx)
	{
		if (m_bindings.find(action) != m_bindings.end())	
		{
			auto binding = m_bindings[action];
			return isKeyUp(binding.keyCode) && binding.playerIdx == playerIdx;
		}

		return false;
	};
	bool InputManager::isKeyPressed(const std::string& action, int playerIdx)
	{
		if (m_bindings.find(action) != m_bindings.end())
		{
			auto binding = m_bindings[action];
			return isKeyPressed(binding.keyCode) && binding.playerIdx == playerIdx;
		}

		return false;
	};


	void InputManager::bind(const std::string& name, int keyCode, int playerIdx)
	{
		m_bindings[name] = { keyCode, playerIdx }; // In die Map werden die beiden Werte gespeichert. (BindingForPlayer)
	};

	void InputManager::unbind(const std::string& name, int playerIdx)
	{
		auto binding_iterator = m_bindings.find(name); // Wenn der Eintrag vorhanden ist, ist der Binding-Iterator ein Iterator, der auf den Wert zeigt. Andernfalls zeigt er ans Ende der Map.
		if (binding_iterator != m_bindings.end() && binding_iterator->second.playerIdx == playerIdx) // `second` ist der zweite Wert in der Map (BindingForPlayer)(keyCode, playerIdx)
		{
			m_bindings.erase(binding_iterator);
		}
	};



	void InputManager::handleEvents(sf::Event& event)
	{
			
		if (event.type == sf::Event::EventType::KeyPressed)
		{
			//std::cout << "keypressed";
			m_isKeyDown[event.key.code] = true;
			m_isKeyPressed[event.key.code] = true;
		}
		else if (event.type == sf::Event::EventType::KeyReleased)
		{
			//std::cout << "keyrelesead";
			m_isKeyUp[event.key.code] = true;
			m_isKeyPressed[event.key.code] = false;
		}
			
	}
