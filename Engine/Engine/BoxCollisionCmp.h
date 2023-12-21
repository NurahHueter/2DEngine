#pragma once
#include "IComponent.h"
#include <SFML/Graphics/Rect.hpp>
#include <memory>

namespace mmt_gd
{
    class RigidBodyCmp; // Forward declaration

    class BoxCollisionCmp : public IComponent , std::enable_shared_from_this< BoxCollisionCmp >
    {
    public:
        BoxCollisionCmp(GameObject& gameObject, sf::FloatRect m_shape)
            : IComponent(gameObject), m_shape(m_shape) {}

        bool init() override;
        void update(float deltaTime) override;

        // Accessors
        const sf::FloatRect& getSize() const { return m_shape; }
        const sf::Vector2f& getPosition() const { return m_position; }
        bool isLogicTrigger() const { return logicTrigger; }
        std::shared_ptr<RigidBodyCmp> getRigidBody() const { return rigidBody; }

        // Setters
        void setLogicTrigger(bool value) { logicTrigger = value; }

        std::shared_ptr<RigidBodyCmp> rigidBody = nullptr;
        
        sf::FloatRect m_shape;
        sf::Vector2f m_position;
        bool logicTrigger = false;
    };
}
