#pragma once
#include "IComponent.h"
#include<memory>
#include <SFML/Graphics.hpp>
namespace mmt_gd
{
	class MouseMoveCmp : public IComponent
	{
	public:
		MouseMoveCmp(GameObject& gameObject, sf::Vector2f targetPosition, float velocity)
				:IComponent(gameObject), targetPosition(targetPosition), velocity(velocity) {};
		bool init() override { return true; };
		void update(float deltaTime) override;

	private:
		sf::Vector2f direction;
		sf::Vector2f targetPosition;
		float velocity;
	};
}