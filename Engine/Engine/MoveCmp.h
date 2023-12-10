#pragma once
#include "IComponent.h"
#include<memory>

class GameObject;
class MoveCmp : public IComponent
{
public:
	MoveCmp(GameObject& gameObject, sf::Vector2f direction, float velocity)
		:IComponent(gameObject), direction(direction), velocity(velocity) {};
	bool init() override {};
	void update(float deltaTime) override;

private:
	sf::Vector2f direction;
	float velocity;
};