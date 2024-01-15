#pragma once
#include "pch.h"
#include "SteeringCmp.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SpriteAnimationCmp.h"
#include "RigidBodyCmp.h"
#include "VectorAlgebra2D.h"

namespace mmt_gd
{
    bool SteeringCmp::init() 
    {
        
        return true;
    };
    void SteeringCmp::update(float deltaTime)
    {
        constexpr float acc = 200.0f; ///< "const" is evaluated at compile time; "const" could be changed at runtime

        sf::Vector2f accVec;
        const auto& animation = gameObject.getComponent<SpriteAnimationCmp>();

        sf::Vector2f distance = m_target - gameObject.getPosition();
        MathUtil::unitVector(distance);
        
        if (std::abs(distance.x) > std::abs(distance.y))
        {
            // Horizontale Bewegung
            accVec = { (distance.x > 0) ? acc : -acc, 0.0f };
            animation->setCurrentAnimation((distance.x > 0) ? MoveRight : MoveLeft);
        }
        else
        {
            // Vertikale Bewegung
            accVec = { 0.0f, (distance.y > 0) ? acc : -acc };
            animation->setCurrentAnimation((distance.y > 0) ? MoveDown : MoveUp);
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