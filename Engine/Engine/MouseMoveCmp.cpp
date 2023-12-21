#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "MouseMoveCmp.h"
namespace mmt_gd
{
    void MouseMoveCmp::update(float deltaTime)
    {

        if (InputManager::instance().isMouseDown("leftclick", 2))
        {
            targetPosition = InputManager::instance().getMousPosition();
        }
        direction = targetPosition - gameObject.getPosition();// Man berechnet den vektor von der Rakte zum MausClick
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance > 1.0f)
        {
            velocity = 2.0f;
        }
        else
        {
            velocity = 0.f;
        }

       sf::Vector2f newPos = gameObject.getPosition() + direction * velocity * deltaTime;
       gameObject.setPosition(newPos);
    };
}