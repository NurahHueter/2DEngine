#pragma once
#include "pch.h"
#include "InputManager.h"


namespace mmt_gd
{
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

	void InputManager::setWindow(sf::RenderWindow& window)
	{
		this->m_window.reset(&window, [](sf::RenderWindow*) {});
	}

	sf::Vector2f InputManager::getMousPosition()
	{
		if (m_window)
		{
			sf::Vector2f worldMousePosition = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
			return worldMousePosition;
		}
	}
}