#pragma once
#include"pch.h"
#include"Rocket.h"
#include"RenderCmp.h"
#include"MoveCmp.h"
#include"InputManager.h"

void Rocket::init() 
{
	renderComponent = std::make_shared<RenderCmp>(std::weak_ptr<GameObject>(shared_from_this()), "../Assets/Hunter1-right.bmp", "rocket");
	renderComponent->init();
	moveComponent = std::make_shared<MoveCmp>(std::weak_ptr<GameObject>(shared_from_this()), sf::Vector2f(0, 0), 200.f);
	moveComponent->init();
	this->setPosition(sf::Vector2f(300, 50));
	
	std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(sf::Vector2f(1.f,0), 300.f, this->getPosition(), 500);
	for (auto it = objectPool[0].begin(); it != objectPool[0].end(); ++it)
	{
		*it = std::make_shared<Projectile>(projectile);
	}
};
void Rocket::draw(sf::RenderWindow& window) 
{
	renderComponent->draw(window);
};
void Rocket::update(float deltatime) 
{
	if (InputManager::instance().isKeyPressed("up", 1))
	{
		moveComponent->setDirection(moveComponent->getDirection() + sf::Vector2f(0, -1));
	}
	if (InputManager::instance().isKeyPressed("down", 1))
	{
		moveComponent->setDirection(moveComponent->getDirection() +  sf::Vector2f(0, 1));
	}
	if (InputManager::instance().isKeyPressed("left", 1))
	{
		moveComponent->setDirection(moveComponent->getDirection() +  sf::Vector2f(-1, 0));
	}
	if (InputManager::instance().isKeyPressed("right", 1))
	{
		moveComponent->setDirection(moveComponent->getDirection() + sf::Vector2f(1, 0));
	}

	if (InputManager::instance().isKeyPressed("shoot", 1))
	{

	}

	moveComponent->update(deltatime);
	moveComponent->setDirection(sf::Vector2f(0, 0));
	renderComponent->update(deltatime);
};