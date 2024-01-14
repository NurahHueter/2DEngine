#pragma once
#include "pch.h"
#include "SteeringCmp.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "VectorAlgebra2D.h"
#include "AIControllerCmp.h"

namespace mmt_gd
{
    bool AIControllerCmp::init()
    {

        return true;
    };
    void AIControllerCmp::update(float deltaTime)
    {
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
        const auto& steering = gameObject.getComponent<SteeringCmp>();


    };
    void AIControllerCmp::attack()
    {
        const auto& steering = gameObject.getComponent<SteeringCmp>();
        gameObject.getComponent<SteeringCmp>()->setTarget(GameObjectManager::instance().getGameObject("Player")->getPosition());

    };
    void AIControllerCmp::flee()
    {
    };
}