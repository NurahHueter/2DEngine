#pragma once
#include "InputManager.h"


namespace sf {

	void InputManager::Init(Window window)
	{
		window.setKeyRepeatEnabled(false);

		window.KeyPressed += OnKeyPressed;
		Event::KeyReleased += OnKeyReleased;

		isKeyDown[(Keyboard::Key::W)] = false;
		isKeyDown[(Keyboard::Key::A)] = false;		
		isKeyDown[(Keyboard::Key::S)] = false;
		isKeyDown[(Keyboard::Key::D)] = false;

		isKeyUp[(Keyboard::Key::W)] = false;
		isKeyUp[(Keyboard::Key::A)] = false;
		isKeyUp[(Keyboard::Key::S)] = false;
		isKeyUp[(Keyboard::Key::D)] = false;

		isKeyPressed[(Keyboard::Key::W)] = false;
		isKeyPressed[(Keyboard::Key::A)] = false;
		isKeyPressed[(Keyboard::Key::S)] = false;
		isKeyPressed[(Keyboard::Key::D)] = false;
	};


	void InputManager::update()
	{
		for (auto& kv : isKeyDown)
		{
			isKeyDown[kv.first] = false;
			//kv.second = false;
		}
		for (auto& kv : isKeyUp) 
		{
			isKeyUp[kv.first] = false;
		}
	};

	bool InputManager::GetKeyPressed(Keyboard::Key key)
	{
		return isKeyPressed.find(key) != isKeyPressed.end() ? isKeyPressed[key] : false;
	};

	bool InputManager::GetKeyDown(Keyboard::Key key)
	{
		return isKeyDown.find(key) != isKeyDown.end() ? isKeyDown[key] : false;
	};

	bool InputManager::GetKeyUp(Keyboard::Key key) 
	{
		return isKeyUp.find(key) != isKeyUp.end() ? isKeyUp[key] : false;
	}
	void OnKeyPressed(const Event::KeyEvent& e) {

	}
	void OnKeyReleased(const Event::KeyEvent& e) {

	}

}