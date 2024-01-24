#pragma once
#include "pch.h"
#include "SteeringCmp.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SpriteAnimationCmp.h"
#include "RigidBodyCmp.h"
#include "VectorAlgebra2D.h"
#include "MapTile.h"
#include "Astar.h"

namespace mmt_gd
{
    bool SteeringCmp::init() 
    {
        int sizeX = gameObject.getComponent<SpriteAnimationCmp>()->getTextureRect().getSize().x;
        int sizeY = gameObject.getComponent<SpriteAnimationCmp>()->getTextureRect().getSize().y;

        //Kachelposition von der AI
        int idxw_player = (gameObject.getPosition().x + (sizeX / 2)) / 16;          //16-> tileGr��e
        int idxh_player = (gameObject.getPosition().y + (sizeY / 2)) / 16;
        //std::cout << "Pos Player X " << idxw_player << "Pos Player Y " << idxh_player << std::endl;

        //Kachelposition vom Target
        int idxw_target = (GameObjectManager::instance().getGameObject("Player")->getPosition().x + (sizeX / 2)) / 16;
        int idxh_target = (GameObjectManager::instance().getGameObject("Player")->getPosition().y + (sizeY / 2)) / 16;

        //std::cout << "Pos Target X " << idxw_target << "Pos Target Y " << idxh_target << std::endl;


        // Create start and goal nodes
        Node start(39, 39, 0, 0); // Assuming g and h are 0 initially
        Node goal(idxw_target, idxh_target, 0, 0); // Assuming g and h are 0 initially

        // Call A* algorithm
        AStar(MapTile::m_LayerKachelWithBuffer, start, goal);

        return true;
    };
    void SteeringCmp::update(float deltaTime)
    {
 
    //    constexpr float acc = 200.0f; ///< "const" is evaluated at compile time; "const" could be changed at runtime

    //     setTarget(GameObjectManager::instance().getGameObject("Player")->getPosition());

    //    sf::Vector2f accVec;
    //    const auto& animation = gameObject.getComponent<SpriteAnimationCmp>();

    //    sf::Vector2f distance = m_target - gameObject.getPosition();
    //    MathUtil::unitVector(distance);
    //    
    //    if (std::abs(distance.x) > std::abs(distance.y))
    //    {
    //        // Horizontale Bewegung
    //        accVec = { (distance.x > 0) ? acc : -acc, 0.0f };
    //        animation->setCurrentAnimation((distance.x > 0) ? "MoveRight" : "MoveLeft");
    //    }
    //    else
    //    {
    //        // Vertikale Bewegung
    //        accVec = { 0.0f, (distance.y > 0) ? acc : -acc };
    //        animation->setCurrentAnimation((distance.y > 0) ? "MoveDown" : "MoveUp");
    //    }

    //    if (auto rigidBodyCmp = gameObject.getComponent<RigidBodyCmp>())
    //    {
    //        rigidBodyCmp->setVelocityP(accVec * deltaTime);
    //        rigidBodyCmp->setVelocityN(rigidBodyCmp->getVelocity() - (rigidBodyCmp->getVelocity() * 0.99f));
    //        rigidBodyCmp->setImpulse(accVec);
    //        rigidBodyCmp->setPosition(rigidBodyCmp->getVelocity(), deltaTime);
    //        gameObject.setPosition(rigidBodyCmp->getPosition());
    //    }

    //    
    //    // Reset acceleration 
    //    accVec = sf::Vector2f(0, 0);
    };
}