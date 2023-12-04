#pragma once
#include "Component.h"
#include<memory>

class GameObject;
class RenderCmp;
class ProjectilePoolCmp : public Component
{
public:
	ProjectilePoolCmp(std::string id, std::weak_ptr<GameObject> gameObject, std::weak_ptr<RenderCmp> renderCmp, float velocity, float timeToLife, int number)
		:Component(id), gameObject(gameObject), velocity(velocity) {};
	void init() override {};
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override {};

private:
	std::weak_ptr<GameObject> gameObject;
	std::weak_ptr<RenderCmp> renderCmp;
	float velocity;
	float timeToLife; 
	int number;
};