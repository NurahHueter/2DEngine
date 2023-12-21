#pragma once
#include "GameObjectManager.h"
#include "BoxCollisionCmp.h"
#include <SFML/Graphics/Rect.hpp>

//struct RigidBody
//{
//     Collision geometry. In the component-based architecture, the
//     collision geometry should be in a separate component, e.g.,
//     BBoxCollisionComponent
//    sf::FloatRect m_shape;
//
//     The debug geometry to visualize the bounding geometry of the object.
//     Can be part of a BBoxCollisionComponent.
//    
//
//     Parameters used for the rigid body physics
//
//    float m_mass;
//    float m_invMass;
//
//    sf::Vector2f m_position;
//
//    std::list<sf::Vector2f> m_forces;   ///< forces constantly applied to object, e.g., gravity
//    std::list<sf::Vector2f> m_impulses; ///< impulses fire only once, e.g., during collision
//
//    sf::Vector2f m_acceleration;
//    sf::Vector2f m_velocity;
//};

namespace mmt_gd
{
struct Manifold
{
    std::shared_ptr<BoxCollisionCmp> m_body1{};
    std::shared_ptr<BoxCollisionCmp> m_body2{};

    float    m_penetration{};
    sf::Vector2f m_normal;
};


    class RigidBodyCmp; 

    class GameObjectManager;
    struct PhysicsManager
    {
        static
            PhysicsManager&
            instance()
        {
            static PhysicsManager s;
            return s;
        } // instance

        PhysicsManager(const PhysicsManager&) = delete;
        PhysicsManager& operator = (const PhysicsManager&) = delete;

       void addBoxCollisionCmp(std::shared_ptr<BoxCollisionCmp> component);

        std::vector<std::shared_ptr<BoxCollisionCmp>> m_bodies;
        std::vector<Manifold>  m_manifolds;
        void update();
        void shutdown();
    private:
        void resolveCollisions(std::vector<Manifold>& m_manifolds);
        bool aabbVsAabb(const sf::FloatRect& a, const sf::FloatRect& b, sf::Vector2f& normal, float& penetration); // returns true if interseciton
        void findCollisions(std::vector<std::shared_ptr<BoxCollisionCmp>>& m_bodies);
        PhysicsManager() {}
        ~PhysicsManager() {}
    };
}
