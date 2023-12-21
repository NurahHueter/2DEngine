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

        const sf::Vector2f& getVelocity() const { return m_velocity; }
        void setVelocity(const sf::Vector2f& newVelocity) { m_velocity = newVelocity; }

        float m_mass;
        //float m_invMass;        
        sf::Vector2f m_velocity;

        std::list<sf::Vector2f> m_forces;   ///< forces constantly applied to object, e.g., gravity
        std::list<sf::Vector2f> m_impulses; ///< impulses fire only once, e.g., during collision

        //sf::Vector2f m_acceleration;
    };
}
