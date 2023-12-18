#pragma once
#include <SFML/System/Vector2.hpp>


namespace mmt_gd
{
    class RigidBodyCmp
    {


    public:
        RigidBodyCmp(float initialMass = 1.0f, const sf::Vector2f& initialVelocity = sf::Vector2f(0.0f, 0.0f))
            : mass(initialMass), velocity(initialVelocity)
        {
        }


        float getMass() const { return mass; }
        void setMass(float newMass) { mass = newMass; }


        sf::Vector2f getVelocity() const { return velocity; }
        void setVelocity(const sf::Vector2f& newVelocity) { velocity = newVelocity; }

    private:
        float mass;
        sf::Vector2f velocity;
    };

}

