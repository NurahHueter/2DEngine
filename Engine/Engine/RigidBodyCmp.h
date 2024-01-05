#pragma once
#include "IComponent.h"
#include "GameObject.h"
#include <SFML/System/Vector2.hpp>

namespace mmt_gd
{
    class RigidBodyCmp : public IComponent
    {
    public:
        RigidBodyCmp(GameObject& gameObject, float mass, const sf::Vector2f velocity)
            : IComponent(gameObject), m_mass(mass), m_velocity(velocity)
        {
            if (auto temP = gameObject.getComponent<RigidBodyCmp>())
            {
                std::cout << "GameObject has allready RigidBody Component! It will be removed" << std::endl;
                gameObject.removeComponent(temP);
            };
        };

        bool init() override { return true; }
        void update(float deltaTime) override {}

        float getMass() const { return m_mass; }
        void setMass(float newMass) { m_mass = newMass; }

        const sf::Vector2f& getVelocity()  { return m_velocity; }
        void setVelocity(const sf::Vector2f& newVelocity) { m_velocity = newVelocity; }
        void setImpulse(const sf::Vector2f& newImpulse) { m_impulse = newImpulse; }
        void setPosition(sf::Vector2f velocity,float deltaTime) { m_position += velocity*deltaTime; }
        sf::Vector2f getPosition() const { return m_position; }

        float m_mass;
        float m_invMass;        
        sf::Vector2f m_velocity;
        sf::Vector2f m_impulse;
        sf::Vector2f m_position;
        std::list<sf::Vector2f> m_forces;   ///< forces constantly applied to object, e.g., gravity
        std::list<sf::Vector2f> m_impulses; ///< impulses fire only once, e.g., during collision

        sf::Vector2f m_acceleration;
    };
}
