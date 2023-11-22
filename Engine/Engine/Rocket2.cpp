#pragma once
#include"pch.h"
#include"Rocket2.h"
#include"RenderCmp.h"
#include"MoveCmp.h"
#include"InputManager.h"
#include"WindowManager.h"

void Rocket2::init()
{
	renderComponent = std::make_shared<RenderCmp>(std::weak_ptr<GameObject>(shared_from_this()), "../Assets/rocket.png", "rocket2");
	renderComponent->init();
	moveComponent = std::make_shared<MoveCmp>(std::weak_ptr<GameObject>(shared_from_this()), sf::Vector2f(0, 0), 100.f);
	moveComponent->init();
	this->setPosition(sf::Vector2f(300, 500));
};
void Rocket2::draw(sf::RenderWindow& window )
{
	renderComponent->draw(window);
};

void Rocket2::update(float deltatime)
{

	if (InputManager::instance().isMouseDown("leftclick", 2))
	{
		targetPosition = InputManager::instance().getMousPosition();
	}
	sf::Vector2f direction = targetPosition - getPosition();// Man berechnet den vektor von der Rakte zum MausClick
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (distance > 1.0f) 
	{
		moveComponent->setDirection(direction);
		moveComponent->setSpeed(2.0f);
	}
	else
	{
		moveComponent->setSpeed(0.f);
	}
	
	moveComponent->update(deltatime);
	renderComponent->update(deltatime);

};