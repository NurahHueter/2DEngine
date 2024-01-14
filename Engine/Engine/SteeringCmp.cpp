#pragma once
#include "pch.h"
#include "SteeringCmp.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SpriteAnimationCmp.h"
#include "RigidBodyCmp.h"

namespace mmt_gd
{
    bool SteeringCmp::init() 
    {
        setTarget(GameObjectManager::instance().getGameObject("Player")->getPosition());
        return true;
    };
    void SteeringCmp::update(float deltaTime)
    {
        constexpr float acc = 1000.0f; ///< "const" is evaluated at compile time; "const" could be changed at runtime

        sf::Vector2f accVec;
        const auto& animation = gameObject.getComponent<SpriteAnimationCmp>();

        sf::Vector2f distance = m_target - gameObject.getPosition();
        
        //std::cout << gameObject.getPlayerIdx() << std::endl;
        if (distance.y > 0)
        {
            accVec = { 0.0f, -acc };
            animation->setCurrentAnimation("MoveUp");
        }
        if (distance.y < 0)
        {
            accVec = { 0.0f, acc };
            animation->setCurrentAnimation("MoveDown");
        }
        if (distance.x < 0)
        {
            accVec = { -acc, 0.0f };
            animation->setCurrentAnimation("MoveLeft");
        }
        if(distance.x > 0)
        {
            accVec = { acc, 0.0f };
            animation->setCurrentAnimation("MoveRight");
        }
        if (auto rigidBodyCmp = gameObject.getComponent<RigidBodyCmp>())
        {
            rigidBodyCmp->setVelocityP(accVec * deltaTime);
            rigidBodyCmp->setVelocityN(rigidBodyCmp->getVelocity() - (rigidBodyCmp->getVelocity() * 0.99f));
            rigidBodyCmp->setImpulse(accVec);
            rigidBodyCmp->setPosition(rigidBodyCmp->getVelocity(), deltaTime);
            gameObject.setPosition(rigidBodyCmp->getPosition());
        }

        // Reset acceleration 
        accVec = sf::Vector2f(0, 0);
    };
}