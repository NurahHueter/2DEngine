#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
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
        GameState(){};
        virtual void init() = 0;
        virtual void exit() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw() = 0;
    };


    
    class MenuState : public GameState
    {
    
    public:
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw() override; 
    };
    class SpaceState : public GameState
    {
    public:
        MapTile mapTile;
        virtual void init() override;
        virtual void exit() override;
        virtual void update(float deltaTime) override;
        virtual void draw() override;
    };
}
