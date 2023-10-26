#pragma once
#include "All_Includes.h";

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

    void Init(Window& window);
    void update();
    bool GetKeyPressed(Keyboard::Key key);
    bool GetKeyDown(Keyboard::Key key);
    bool GetKeyUp(Keyboard::Key key);
    void handleEvents(sf::Event& event);


private:

    std::map<Keyboard::Key, bool> m_isKeyDown{};
    std::map<Keyboard::Key, bool> m_isKeyPressed {};
    std::map<Keyboard::Key, bool> m_isKeyUp {};
	
 //   void OnKeyPressed(const Event::KeyEvent& e) ;
	//void OnKeyReleased(const Event::KeyEvent& e);
	

    InputManager() {}
    ~InputManager() {}

};

}