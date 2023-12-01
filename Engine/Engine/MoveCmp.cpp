#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "MoveCmp.h"

void MoveCmp::update(float deltaTime) 
{
	if (std::shared_ptr<GameObject> tempP = gameObject.lock()) //check if Gameobject is nullptr
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
        else
        {
            direction = sf::Vector2f(0, 0);
        }

        sf::Vector2f newPos = tempP->getPosition() + direction * velocity * deltaTime;
        tempP->setPosition(newPos);
    }
};