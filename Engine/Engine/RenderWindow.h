#pragma once
#include <memory>
class RenderWindow {
public:
    RenderWindow() : m_window(m_mode, "SFML Window")
    {
        m_window.setVerticalSyncEnabled(true);
    };

    sf::VideoMode m_mode = { 800, 600 };
    sf::RenderWindow m_window;
    
};

extern std::shared_ptr<RenderWindow> g_window_instance;