#pragma once
#include <map>

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

    void Init(sf::Window& window);
    void update();
    bool GetKeyPressed(sf::Keyboard::Key key);
    bool GetKeyDown(sf::Keyboard::Key key);
    bool GetKeyUp(sf::Keyboard::Key key);
    void handleEvents(sf::Event& event);


private:

    std::map<sf::Keyboard::Key, bool> m_isKeyDown{};
    std::map<sf::Keyboard::Key, bool> m_isKeyPressed {};
    std::map<sf::Keyboard::Key, bool> m_isKeyUp {};
	
 //   void OnKeyPressed(const Event::KeyEvent& e) ;
	//void OnKeyReleased(const Event::KeyEvent& e);
	

    InputManager() {}
    ~InputManager() {}

};
