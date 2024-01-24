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
        playerPosition = GameObjectManager::instance().getGameObject("Player")->getPosition();
        distance_x = std::abs(playerPosition.x - gameObject.getPosition().x);
        distance_y = std::abs(playerPosition.y - gameObject.getPosition().y);

        if (distance_x < m_attackRange || distance_y < m_attackRange)
        {
            currentState = Attack;
        }
        if (distance_x > m_attackRange || distance_y > m_attackRange)
        {
            currentState = Patrol;
        }
        if (gameObject.getComponent<HealthCmp>()->getHealth() == 1
            && (distance_x < m_attackRange || distance_y < m_attackRange))
        {
            currentState = Flee;
        };

        switch (currentState)
        {
        case Patrol:
            patrol();
            break;
        case Attack:
            attack();
            break;
        case Flee:
            flee();
            break;
        default:
            break;
        }
    };
    void AIControllerCmp::patrol()
    {
        
        if (m_patrolPoints.size() > 1)
        {
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
    };
    void AIControllerCmp::attack()
    {
        gameObject.getComponent<SteeringCmp>()->setTarget(playerPosition);
        gameObject.getComponent<ProjectileCmp>()->shoot(playerPosition);

    };
    void AIControllerCmp::flee()
    {
        auto playerPosition = GameObjectManager::instance().getGameObject("Player")->getPosition();
        sf::Vector2f fleePoint = sf::Vector2f(playerPosition.x * -1, playerPosition.y * -1);

        gameObject.getComponent<SteeringCmp>()->setTarget(fleePoint);
    };
}