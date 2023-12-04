#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "MouseMoveCmp.h"

void MouseMoveCmp::update(float deltaTime)
{
    if (std::shared_ptr<GameObject> tempP = gameObject.lock()) //check if Gameobject is nullptr
    {
        if (InputManager::instance().isMouseDown("leftclick", 2))
        {
            targetPosition = InputManager::instance().getMousPosition();
        }
        direction = targetPosition - tempP->getPosition();// Man berechnet den vektor von der Rakte zum MausClick
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance > 1.0f)
        {
            velocity = 2.0f;
        }
        else
        {
            velocity = 0.f;
        }

        sf::Vector2f newPos = tempP->getPosition() + direction * velocity * deltaTime;
        tempP->setPosition(newPos);
        direction = sf::Vector2f(0, 0);
    }
};