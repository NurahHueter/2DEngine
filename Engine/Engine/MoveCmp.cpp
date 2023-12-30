#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteAnimationCmp.h"
#include "MoveCmp.h"
#include "RigidBodyCmp.h"
namespace mmt_gd
{
    void MoveCmp::update(float deltaTime)
    {
        //if(gameObject.getComponent<RigidBodyCmp>())
        const auto& animation = gameObject.getComponent<SpriteAnimationCmp>();
        if (InputManager::instance().isKeyPressed("up", 1))
        {
            direction = sf::Vector2f(0, -1);
            animation->setCurrentAnimation("MoveUp");
        }
        if (InputManager::instance().isKeyPressed("down", 1))
        {
            direction = sf::Vector2f(0, 1);
            animation->setCurrentAnimation("MoveDown");
        }
        if (InputManager::instance().isKeyPressed("left", 1))
        {
            direction = sf::Vector2f(-1, 0);
            animation->setCurrentAnimation("MoveLeft");
        }
        if (InputManager::instance().isKeyPressed("right", 1))
        {
            direction = sf::Vector2f(1, 0);
            animation->setCurrentAnimation("MoveRight");
        }

        sf::Vector2f newPos = gameObject.getPosition() + direction * velocity * deltaTime;
        gameObject.setPosition(newPos);
        direction = sf::Vector2f(0, 0);

    };
}