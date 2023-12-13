#pragma once
#include "IComponent.h"
#include<memory>

class GameObject;
class MouseMoveCmp final : public IComponent
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