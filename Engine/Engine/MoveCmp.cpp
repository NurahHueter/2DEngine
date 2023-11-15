#pragma once
#include "pch.h"
#include "GameObject.h"
#include "MoveCmp.h"

void MoveCmp::update(float deltaTime) 
{
	if (std::shared_ptr<GameObject> tempP = gameObject.lock()) //check if Gameobject is nullptr
	{
		sf::Vector2f newPos = tempP->getPosition() + direction * speed * deltaTime;
		tempP->setPosition(newPos);
	}
};
void MoveCmp::setDirection(sf::Vector2f direction)
{
	this->direction = direction;
};
void MoveCmp::setSpeed(float speed)
{
	this->speed = speed;
};