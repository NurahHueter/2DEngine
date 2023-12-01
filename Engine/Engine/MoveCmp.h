#pragma once
#pragma once
#include "Component.h"
#include<memory>

class GameObject;
class MoveCmp : public Component
{
public:
	MoveCmp(std::weak_ptr<GameObject> gameObject, sf::Vector2f direction, float velocity)
		:Component(id), gameObject(gameObject), direction(direction), velocity(velocity) {};
	void init() override {};
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override {};

private:
	std::weak_ptr<GameObject> gameObject;
	sf::Vector2f direction;
	float velocity;
};