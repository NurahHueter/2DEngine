#pragma once
#include <memory>
#include "GameObject.h"
class RenderCmp;
class MoveCmp;
class Projectile : public GameObject, public std::enable_shared_from_this<Projectile>
{
public:
	Projectile(sf::Vector2f direction, float speed, sf::Vector2f startPosition, float lifeDistance) : direction(direction), speed(speed), startPosition(startPosition), lifeDistance(lifeDistance) {};
	void init() override;
	void draw(sf::RenderWindow& window) override;
	void update(float deltatime) override;

private:
	sf::Vector2f startPosition;
	float lifeDistance;
	bool inUse = false;
	float speed;
	sf::Vector2f direction;
	std::shared_ptr<RenderCmp> renderComponent;
	std::shared_ptr<MoveCmp> moveComponent;
};