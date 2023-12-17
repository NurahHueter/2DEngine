    //GameState.h
    #pragma once
    #include <SFML/Graphics/RenderWindow.hpp>
    #include "GameObjectManager.h"
    #include "MapTile.h"
namespace mmt_gd
{
    class GameObject;
    class GameStateManager;
    class GameState
    {
    public:
        MapTile mapTile;
        virtual void init() = 0;
        virtual void exit() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;

    protected:
        GameStateManager* manager;
        std::vector<std::string> assets;
    };

    class MenuState : public GameState
    {
    public:
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw(sf::RenderWindow& window) override;
    private:
        GameObjectManager m_gameObjectManager;
    };

    class MainState : public GameState
    {
    public:
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw(sf::RenderWindow& window) override;

    private:
        GameObjectManager m_gameObjectManager;
    };
}
