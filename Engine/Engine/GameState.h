    //GameState.h
    #pragma once
    #include <SFML/Graphics/RenderWindow.hpp>

    class GameStateManager;
    class GameState
    {
    public:
        virtual void init() = 0;
        virtual void exit() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;

    private:
        GameStateManager* manager;
    };

    class MenuState : public GameState
    {
    public:
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw(sf::RenderWindow& window) override;
    private:
        sf::Sprite spriteLava;
    };

    class MainState : public GameState
    {
    public:
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw(sf::RenderWindow& window) override;

    private:
        sf::Sprite sprite;
    };
