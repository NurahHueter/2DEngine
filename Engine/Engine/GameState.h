    //GameState.h
    #pragma once
    #include <SFML/Graphics/RenderWindow.hpp>
    #include "GameObjectManager.h"
    #include "RenderManager.h"
    #include "MapTile.h"
    #include "PhysicsManager.h"
namespace mmt_gd
{
    class GameObject;
    class GameStateManager;
    class GameState
    {
    public:
        GameState(sf::RenderWindow& window) : m_window(window){};
        virtual void init() = 0;
        virtual void exit() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw() = 0;

    protected:
        sf::RenderWindow& m_window;
        std::vector<std::string> assets;
    };


    
    class MenuState : public GameState
    {
    
    public:
        MenuState(sf::RenderWindow& m_window) : GameState(m_window) {}
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw() override; 
    private:
        GameObjectManager m_gameObjectManager;
    };

    class MainState : public GameState
    {
    public:
        MainState(sf::RenderWindow& m_window) : GameState(m_window), m_RenderManager(m_window) {}
        MapTile mapTile;
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw() override;
    private:
        GameObjectManager m_gameObjectManager;
        RenderManager m_RenderManager;
    };
    class SpaceState : public GameState
    {
    public:
        SpaceState(sf::RenderWindow& m_window) : GameState(m_window), m_RenderManager(m_window) {}
        MapTile mapTile;
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw() override;
    private:
        GameObjectManager m_gameObjectManager;
        RenderManager m_RenderManager;
    };
}
