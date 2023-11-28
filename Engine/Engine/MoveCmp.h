#pragma once
#pragma once
#include "Component.h"
#include<memory>

class GameObject;
class MoveCmp : public Component
{
public:
	MoveCmp(std::weak_ptr<GameObject> gameObject, sf::Vector2f direction, float speed)
		:Component(id), gameObject(gameObject), direction(direction), speed(speed) {};
	void init() override {};
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override {};
	void setDirection(sf::Vector2f direction);
	void setSpeed(float speed);
	sf::Vector2f getDirection();
	float getSpeed();

private:
	std::weak_ptr<GameObject> gameObject;
	sf::Vector2f direction;
	float speed;
};