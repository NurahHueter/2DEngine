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
        int idxw_player = (gameObject.getPosition().x + (m_sizeX / 2)) / MapTile::m_tileSize.x;          //16-> tileSize
        int idxh_player = (gameObject.getPosition().y + (m_sizeY / 2)) / MapTile::m_tileSize.x;

        //Kachelposition vom Target
        int idxw_target = (GameObjectManager::instance().getGameObject("Player")->getPosition().x + (m_sizeX / 2)) / MapTile::m_tileSize.x;
        int idxh_target = (GameObjectManager::instance().getGameObject("Player")->getPosition().y + (m_sizeX / 2)) / MapTile::m_tileSize.x;


        // Create start and goal nodes
        Node start(13, 62, 0, 0); // Assuming g and h are 0 initially
        Node goal(39, 39, 0, 0); // Assuming g and h are 0 initially

        // Call A* algorithm
        m_pathlist = AStar(MapTile::m_LayerKachelWithBuffer, start, goal);

        std::cout << "Steps Amount: " << m_pathlist.size() << std::endl;
        std::cout << "Path: ";

        for (auto it = m_pathlist.rbegin(); it != m_pathlist.rend(); ++it)
        {
            std::cout << "(" << it->second << ", " << it->first << ") ";            //ist dann x, y denk ich
        }
        std::cout << std::endl;
       
        return true;
    };
    void SteeringCmp::update(float deltaTime)
    {
        //Werte von den Kacheln ausgeben
        //std::cout << MapTile::m_LayerKachel[0][0] << std::endl;
        int sizeX = gameObject.getComponent<SpriteAnimationCmp>()->getTextureRect().getSize().x;
        int sizeY = gameObject.getComponent<SpriteAnimationCmp>()->getTextureRect().getSize().y;
          //Kachelposition vom Target
        int idxw_target = (GameObjectManager::instance().getGameObject("Player")->getPosition().x + (sizeX / 2)) / 16;
        int idxh_target = (GameObjectManager::instance().getGameObject("Player")->getPosition().y + (sizeY / 2)) / 16;

        static sf::Clock movementClock; // Static ensures the clock is created only once

        if (movementClock.getElapsedTime().asSeconds() >= 0.1f)
        {
            if (!m_pathlist.empty())
            {
                auto path = m_pathlist.rbegin(); // Get the next path

                nextTarget = sf::Vector2f(path->second * 16, path->first * 16);

                m_pathlist.pop_back(); // Remove the used path from the list

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