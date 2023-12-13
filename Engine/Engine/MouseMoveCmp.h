#pragma once
#include "IComponent.h"
#include<memory>
#include <SFML/Graphics.hpp>
namespace mmt_gd
{
public:
	MouseMoveCmp(GameObject& gameObject, sf::Vector2f direction, float velocity)
		:IComponent(gameObject), direction(direction), velocity(velocity) {};
	bool init() override { return true; };
	void update(float deltaTime) override;

	private:
		sf::Vector2f direction;
		sf::Vector2f targetPosition;
		float velocity;
	};
}