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
        //TODO Richtigen Player nehm,en
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
        
    //    constexpr float acc = 200.0f; ///< "const" is evaluated at compile time; "const" could be changed at runtime
        static sf::Clock movementClock; // Static ensures the clock is created only once

        int sizeX = gameObject.getComponent<SpriteAnimationCmp>()->getTextureRect().getSize().x;
        int sizeY = gameObject.getComponent<SpriteAnimationCmp>()->getTextureRect().getSize().y;

        int idxw_player = (gameObject.getPosition().x + (sizeX / 2)) / 16; // 16-> tileGröße
        if (movementClock.getElapsedTime().asSeconds() >= 0.1f)
        {
            if (!m_pathlist.empty())
            {
                auto path = m_pathlist.rbegin(); // Get the next path

                gameObject.setPosition(path->second * 16, path->first * 16);

                m_pathlist.pop_back(); // Remove the used path from the list

                movementClock.restart(); // Restart the clock for the next second
            }
        }

        // Rest of your update logic...
    }
}