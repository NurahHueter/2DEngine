#pragma once

#include <iostream>
#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>

namespace sf {

struct InputManager
{
    static
        InputManager&
        instance()
    {
        static InputManager s;
        return s;
    } // instance

    InputManager(const InputManager&) = delete;
    InputManager& operator = (const InputManager&) = delete;

    void Init(Window window);
    void update();
    bool GetKeyPressed(Keyboard::Key key);
    bool GetKeyDown(Keyboard::Key key);
    bool GetKeyUp(Keyboard::Key key);


private:

    std::map<Keyboard::Key, bool> isKeyDown{};
    std::map<Keyboard::Key, bool> isKeyPressed {};
    std::map<Keyboard::Key, bool> isKeyUp {};
	
    void OnKeyPressed(const Event::KeyEvent& e) ;
	void OnKeyReleased(const Event::KeyEvent& e);
	

    InputManager() {}
    ~InputManager() {}

};

}