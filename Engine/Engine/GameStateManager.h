// GameStateManager.h
#pragma once
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>

class GameState; // forward declaration to avoid circular header file dependency

class GameStateManager
{
public:
    static GameStateManager& instance() {
        static GameStateManager s;
        return s;
    }

    GameStateManager(const GameStateManager&) = delete;
    GameStateManager& operator=(const GameStateManager&) = delete;

    GameStateManager() : currentState(nullptr) {}

    void update(float deltaTime);
    void draw(sf::RenderWindow& m_window);
    void Init();
    void setState(std::string stateName);

private:
    ~GameStateManager() {}
    std::map<std::string, std::shared_ptr<GameState>> states;
    std::shared_ptr<GameState> currentState;
};