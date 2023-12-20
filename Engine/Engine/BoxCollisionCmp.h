#pragma once
#include "IComponent.h"
#include <SFML/Graphics/Rect.hpp>
#include <memory>

namespace mmt_gd
{
    class RigidBodyCmp; // Forward declaration

    class BoxCollisionCmp : public IComponent
    {
    public:
        BoxCollisionCmp(GameObject& gameObject, const sf::Vector2f& initialSize = sf::Vector2f(10.0f, 10.0f),
            const sf::Vector2f& initialPosition = sf::Vector2f(10.0f, 10.0f),
            std::shared_ptr<RigidBodyCmp> initialRigidBody = nullptr, bool isLogicTrigger = false)
            : IComponent(gameObject), size(initialSize), position(initialPosition), ownRigidBody(initialRigidBody), logicTrigger(isLogicTrigger) {}

        bool init() override { return true; }
        void update(float deltaTime) override {}

        // Accessors
        const sf::Vector2f& getSize() const { return size; }
        const sf::Vector2f& getPosition() const { return position; }
        bool isLogicTrigger() const { return logicTrigger; }
        std::shared_ptr<RigidBodyCmp> getRigidBody() const { return ownRigidBody; }

        // Setters
        void setLogicTrigger(bool value) { logicTrigger = value; }

    private:
        sf::Vector2f size;
        sf::Vector2f position;
        std::shared_ptr<RigidBodyCmp> ownRigidBody;
        bool logicTrigger;
    };
}
