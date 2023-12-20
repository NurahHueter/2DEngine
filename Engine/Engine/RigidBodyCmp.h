#pragma once
#include "IComponent.h"
#include <SFML/System/Vector2.hpp>

namespace mmt_gd
{
    class RigidBodyCmp : public IComponent
    {
    public:
        RigidBodyCmp(GameObject& gameObject, float initialMass = 1.0f, const sf::Vector2f& initialVelocity = sf::Vector2f(0.0f, 0.0f))
            : IComponent(gameObject), mass(initialMass), velocity(initialVelocity) {}

        bool init() override { return true; }
        void update(float deltaTime) override {}

        float getMass() const { return mass; }
        void setMass(float newMass) { mass = newMass; }

        const sf::Vector2f& getVelocity() const { return velocity; }
        void setVelocity(const sf::Vector2f& newVelocity) { velocity = newVelocity; }

    private:
        float mass;
        sf::Vector2f velocity;
    };
}
