#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "MoveCmp.h"
#include "RigidBodyCmp.h"
namespace mmt_gd
{
    void MoveCmp::update(float deltaTime)
    {
        //if(gameObject.getComponent<RigidBodyCmp>())
        constexpr float acc = 1000.0f; ///< "const" is evaluated at compile time; "const" could be changed at runtime

        sf::Vector2f accVec;
        if (InputManager::instance().isKeyPressed("up", 1))
        {
            accVec = { 0.0f, -acc };
        }
        if (InputManager::instance().isKeyPressed("down", 1))
        {
            accVec = { 0.0f, acc };
        }
        if (InputManager::instance().isKeyPressed("left", 1))
        {
            accVec = { -acc, 0.0f };
        }
        if (InputManager::instance().isKeyPressed("right", 1))
        {
            accVec = { acc, 0.0f };
        }

         velocity += accVec * deltaTime;
        // friction
        velocity *= 0.99f;


        sf::Vector2f newPos = gameObject.getPosition() + velocity * deltaTime;
        gameObject.setPosition(newPos);

        // Reset acceleration 
        accVec = sf::Vector2f(0, 0);

    };
}