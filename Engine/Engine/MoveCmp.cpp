#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "MoveCmp.h"

void MoveCmp::update(float deltaTime) 
{

        if (InputManager::instance().isKeyPressed("up", 1))
        {
         direction = sf::Vector2f(0, -1);
        }
        if (InputManager::instance().isKeyPressed("down", 1))
        {
            direction = sf::Vector2f(0, 1);
        }
        if (InputManager::instance().isKeyPressed("left", 1))
        {
            direction = sf::Vector2f(-1, 0);
        }
        if (InputManager::instance().isKeyPressed("right", 1))
        {
            direction = sf::Vector2f(1, 0);
        }

        sf::Vector2f newPos = gameObject.getPosition() + direction * velocity * deltaTime;
        gameObject.setPosition(newPos);
        direction = sf::Vector2f(0, 0);
};