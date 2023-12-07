    //GameState.h
    #pragma once
    #include <SFML/Graphics/RenderWindow.hpp>
    #include "MapTile.h"
   
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
        std::map<std::string, std::shared_ptr<GameObject>> gameObjects = {};
        
    };

    class MenuState : public GameState
    {
    public:
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw(sf::RenderWindow& window) override;
    };

    class MainState : public GameState
    {
    public:
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw(sf::RenderWindow& window) override;

    private:
        int switchCount = 0;
    };
