    //GameState.h
    #pragma once
    #include <SFML/Graphics/RenderWindow.hpp>
   
    class GameObject;
    class GameStateManager;
    class GameState
    {
    public:
        virtual void init() = 0;
        virtual void exit() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
 
    protected:
        GameStateManager* manager;
        std::map<std::string, GameObject> gameObjects = {};
        
    };

    class MenuState : public GameState
    {
    public:
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw(sf::RenderWindow& window) override;
    private:
        bool setCamera = false;
       
    };

    class MainState : public GameState
    {
    public:
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw(sf::RenderWindow& window) override;

    private:
        bool setCamera = false;
        std::shared_ptr<Background> background;
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Rocket> rocket;
        std::shared_ptr<Rocket2> rocket2;
    };
