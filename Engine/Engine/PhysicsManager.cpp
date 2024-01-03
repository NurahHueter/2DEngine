#pragma once

#include "pch.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "PhysicsManager.h"
#include "RigidBodyCmp.h"
#include "GameObjectManager.h"
namespace mmt_gd
{
     void PhysicsManager::addBoxCollisionCmp(std::weak_ptr<BoxCollisionCmp> component)
     {
             m_bodies.push_back(component);
     }

    bool PhysicsManager::aabbVsAabb(const sf::FloatRect& a, const sf::FloatRect& b, sf::Vector2f& normal, float& penetration)
    {
        auto getCenter = [](const sf::FloatRect& rect) -> sf::Vector2f
            { return sf::Vector2f(rect.left, rect.top) + 0.5f * sf::Vector2f(rect.width, rect.height); };

        //std::cout << " b pos x" << b.getPosition().x << std::endl;
        //std::cout << " b pos y" << b.getPosition().y << std::endl;

        //std::cout << " a pos x" << a.getPosition().x << std::endl;
        //std::cout << " a pos y" << a.getPosition().y << std::endl;

        sf::Vector2f n = getCenter(b) - getCenter(a); // Vector from A to B
        float    a_extent = a.width * 0.5f;              // Calculate half extents along x axis
        float    b_extent = b.width * 0.5f;
        float    x_overlap = a_extent + b_extent - abs(n.x); // Calculate overlap on x axis
        // SAT test on x axis
        if (x_overlap > 0)
        {
            float a_extent = a.height * 0.5f; // Calculate half extents along y axis
            float b_extent = b.height * 0.5f;
            float y_overlap = a_extent + b_extent - abs(n.y); // Calculate overlap on y axis

            // SAT test on y axis
            if (y_overlap > 0)
            {
                // Find out which axis is axis of least penetration
                if (x_overlap < y_overlap)
                {
                    // Point towards B knowing that n points from A to B
                    if (n.x < 0)
                        normal = sf::Vector2f(1.0f, 0.0f);
                    else
                        normal = sf::Vector2f(-1.0f, 0.0f);
                    penetration = x_overlap;
                    return true;
                }
                else
                {
                    // Point towards B knowing that n points from A to B
                    if (n.y < 0)
                        normal = sf::Vector2f(0, 1);
                    else
                        normal = sf::Vector2f(0, -1);
                    penetration = y_overlap;
                    return true;
                }
            }
        }
        return false;
    }

    void PhysicsManager::update()
    {
        m_manifolds.clear();
        findCollisions(m_bodies);
        resolveCollisions(m_manifolds);
    }
 
    void PhysicsManager::findCollisions(std::vector<std::weak_ptr<BoxCollisionCmp>>& m_bodies)
    {
       
        //checks if all ptr have a reverence and makes temp shared ptr
        std::vector<std::shared_ptr<BoxCollisionCmp>> bodies;
        for (auto body : m_bodies)
        {
            if (std::shared_ptr<BoxCollisionCmp> tempP = body.lock())
            {
                bodies.push_back(tempP);
            }
        }

        for (auto itA = bodies.begin(); itA != bodies.end(); ++itA)
        {
           
            auto& body1 = *itA;
            for (auto itB = itA; itB != bodies.end(); ++itB)
            {
               
                if (itB == itA)
                    continue;
           
                auto& body2 = *itB;
                // if both object don't have a mass or body is the same skip
                if (!body1->rigidBody && !body2->rigidBody)
                    continue;

              
                sf::Transform body1Transform;
                body1Transform.translate(body1->m_position);
                sf::Transform body2Transform;
                body2Transform.translate(body2->m_position);

                sf::Vector2f normal;
                float    penetration = NAN;
                if (aabbVsAabb(body1Transform.transformRect(body1->m_shape),
                    body2Transform.transformRect(body2->m_shape),
                    normal,
                    penetration))
                {
                    /*std::cout << "ALARM!!";*/
                    Manifold manifold;
                    manifold.m_body1 = body1;
                    manifold.m_body2 = body2;
                    manifold.m_normal = normal;
                    manifold.m_penetration = penetration;

                    m_manifolds.push_back(manifold);
                }
            }
        }
    }

    void PhysicsManager::resolveCollisions( std::vector<Manifold>& m_manifolds)
    {
        for (auto man : m_manifolds)
        {
            // TODO: implement simple collision resolution without restitution. see slides for formulas
            // TODO: add restitution to collision resolution (j)
            // HINT: pay attention to the direction of the normal and relative velocity.
            sf::Vector2f rv = man.m_body1->rigidBody->m_velocity - man.m_body2->rigidBody->m_velocity;
            // std::cout << rv.y;  -> 0/0
            // Calculate relative velocity in terms of the normal direction
            float velAlongNormal = rv.x * man.m_normal.x + rv.y * man.m_normal.y;
            //std::cout << velAlongNormal;   ->0
            //std::cout << man.m_body2->rigidBody->m_velocity.y;  ->200/200
            // Do not resolve if velocities are separating
            if (velAlongNormal > 0)
            {
                return;
            }

            // Apply impulse

            sf::Vector2f impulse = velAlongNormal * man.m_normal;
            //std::cout << man.m_normal.x; von rechts nach links 1, von links nach rechts -1 von oben nach unten und unten nachboen 0
            man.m_body1->rigidBody->m_velocity -= 0.5f * impulse;
            man.m_body2->rigidBody->m_velocity += 0.5f * impulse;
            // TODO: implement positional correction (see slides)
        }
    }

    void PhysicsManager::shutdown()
    {
        m_manifolds.clear();
        m_bodies.clear();
    }

}