#pragma once
#include "GameObjectManager.h"
#include <SFML/Graphics/Rect.hpp>

struct RigidBody
{
    // Collision geometry. In the component-based architecture, the
    // collision geometry should be in a separate component, e.g.,
    // BBoxCollisionComponent
    sf::FloatRect m_shape;

    // The debug geometry to visualize the bounding geometry of the object.
    // Can be part of a BBoxCollisionComponent.
    sf::RectangleShape m_debugGeometry;

    // Parameters used for the rigid body physics

    float m_mass;
    float m_invMass;

    sf::Vector2f m_position;

    std::list<sf::Vector2f> m_forces;   ///< forces constantly applied to object, e.g., gravity
    std::list<sf::Vector2f> m_impulses; ///< impulses fire only once, e.g., during collision

    sf::Vector2f m_acceleration;
    sf::Vector2f m_velocity;
};

struct Manifold
{
    RigidBody* m_body1{};
    RigidBody* m_body2{};

    float    m_penetration{};
    sf::Vector2f m_normal;
};


namespace mmt_gd
{
    class RigidBodyCmp; // Forward declaration

    class GameObjectManager;
    class PhysicsManager
    {
    public:

        RigidBody createBody(const float mass, const sf::FloatRect& aabb, const sf::Vector2f& position);
       bool aabbVsAabb(const sf::FloatRect& a, const sf::FloatRect& b, sf::Vector2f& normal, float& penetration); // returns true if interseciton
        void findCollisions(std::vector<RigidBody>& m_bodies, GameObject& gameObject1, GameObject& gameObject2);
       
        void init(sf::Vector2f& rocketOnePosition, sf::Vector2f& rocketTwoPosition);
        std::vector<RigidBody> m_bodies;
        std::vector<Manifold>  m_manifolds;
        void update(std::vector<RigidBody>& m_bodies);
        GameObjectManager m_gameObjectManager;
        void resolveCollisions(std::vector<Manifold>& m_manifolds);
       
       /*
        void shutdown();
        void update(float fDeltaTime);*/
    
    };
}
