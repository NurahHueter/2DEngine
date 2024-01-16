#pragma once
#include "pch.h"
#include "SteeringCmp.h"
#include "ProjectileCmp.h"
#include "HealthCmp.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "VectorAlgebra2D.h"
#include "AIControllerCmp.h"

namespace mmt_gd
{
    void AIControllerCmp::addPatrolPoint(sf::Vector2f point)
    {
        m_patrolPoints.push_back(point);
    };
    void AIControllerCmp::update(float deltaTime)
    {
        switch (currentState)
        {
        case Patrol:
            patrol();
            break;
        //case Attack:
        //    attack();
        //    break;
        //case Flee:
        //    flee();
        //    break;
        default:
            break;
        }
    };
    void AIControllerCmp::patrol()
    {
        auto playerPosition = GameObjectManager::instance().getGameObject("Player")->getPosition();
        if (m_patrolPoints.size() > 1)
        {
            std::cout << m_currentWayPoint << std::endl;
            gameObject.getComponent<SteeringCmp>()->setTarget(m_patrolPoints[m_currentWayPoint]);

            float distanceToTarget = MathUtil::length(m_patrolPoints[m_currentWayPoint] - gameObject.getPosition());
            float patrolRadius = 20.0f;
            if (distanceToTarget <= patrolRadius)
            {
                m_currentWayPoint++;
                if (m_currentWayPoint >= m_patrolPoints.size())
                {
                    m_currentWayPoint = 0;
                }
            }
        }


        //if (std::abs(playerPosition.x - gameObject.getPosition().x) < m_attackRange 
        //    || std::abs(playerPosition.y - gameObject.getPosition().y) < m_attackRange)
        //{
        //    currentState = Attack;
        //}
        //if (gameObject.getComponent<HealthCmp>()->getHealth() == 1 && (playerPosition.x - gameObject.getPosition().x < m_attackRange 
        //    || std::abs(playerPosition.y - gameObject.getPosition().y) < m_attackRange))
        //{
        //    currentState = Flee;
        //};
    };
    void AIControllerCmp::attack()
    {
        auto playerPosition = GameObjectManager::instance().getGameObject("Player")->getPosition();
        gameObject.getComponent<SteeringCmp>()->setTarget(playerPosition);
        gameObject.getComponent<ProjectileCmp>()->shoot(playerPosition);

        if (std::abs(playerPosition.x - gameObject.getPosition().x) > m_attackRange 
            || std::abs(playerPosition.y - gameObject.getPosition().y) > m_attackRange)
        {
            currentState = Patrol;
        }
        if (gameObject.getComponent<HealthCmp>()->getHealth() == 1 
            && (playerPosition.x - gameObject.getPosition().x < m_attackRange 
                || std::abs(playerPosition.y - gameObject.getPosition().y) < m_attackRange))
        {
            currentState = Flee;
        };
    };
    void AIControllerCmp::flee()
    {
        auto playerPosition = GameObjectManager::instance().getGameObject("Player")->getPosition();
        sf::Vector2f fleePoint = sf::Vector2f(playerPosition.x * -1, playerPosition.y * -1);

        gameObject.getComponent<SteeringCmp>()->setTarget(fleePoint);

        if (playerPosition.x - gameObject.getPosition().x > m_fleeRange 
            || std::abs(playerPosition.y - gameObject.getPosition().y < m_fleeRange))
        {
            currentState = Patrol;
        };
    };
}