#pragma once
#include "IComponent.h"
#include<memory>
#include <SFML/Graphics.hpp>
namespace mmt_gd
{
	class MouseMoveCmp : public IComponent
	{
	public:
		MouseMoveCmp(GameObject& gameObject, float velocity)
				:IComponent(gameObject), direction(direction), velocity(velocity) {};
		bool init() override { return true; };
		void update(float deltaTime) override;

	private:
		sf::Vector2f direction = {0, 0};
		sf::Vector2f targetPosition;
		float velocity;
	};
}