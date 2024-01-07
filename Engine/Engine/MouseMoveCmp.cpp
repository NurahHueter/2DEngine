#pragma once
#include "pch.h"
#include "GameObject.h"
#include "InputManager.h"
#include "MouseMoveCmp.h"
#include "RigidBodyCmp.h"
namespace mmt_gd
{
    void MouseMoveCmp::update(float deltaTime)
    {
        //maus ist schlecht, da er schräg fahren kann, für den impuls (kommt er von oben, unten, links, rechts
       
        //nach dem aufprall soll sie stehen bleiben

        if (auto rigidBodyCmp = gameObject.getComponent<RigidBodyCmp>())
        {
            if (InputManager::instance().isMouseDown("leftclick", 2))
            {
                targetPosition = InputManager::instance().getMousPosition();
                rigidBodyCmp->m_velocity = sf::Vector2f(0.f, 0.f);
            }
            direction = targetPosition - gameObject.getPosition();// Man berechnet den vektor von der Rakte zum MausClick
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);


            if (distance > 2.0f)
            {
                
                rigidBodyCmp->m_velocity = sf::Vector2f((direction.x / distance), (direction.y / distance)) * velocity;
                std::cout << rigidBodyCmp->m_velocity.x << std::endl;
            }
            else
            {
                rigidBodyCmp->m_velocity = sf::Vector2f(0.f, 0.f);
            }

         

            //rigidBodyCmp->setImpulse(accVec); problem
            rigidBodyCmp->setPosition(rigidBodyCmp->m_velocity, deltaTime); 
            gameObject.setPosition(rigidBodyCmp->m_position);
        }
  
    };
}