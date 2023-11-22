#pragma once
#include"pch.h"
#include"Projectile.h"
#include"RenderCmp.h"
#include"MoveCmp.h"
#include"InputManager.h"

void Projectile::init()
{
	renderComponent = std::make_shared<RenderCmp>(std::weak_ptr<GameObject>(shared_from_this()), "../Assets/bulletright.bmp", "projectile");
	renderComponent->init();
	moveComponent = std::make_shared<MoveCmp>(std::weak_ptr<GameObject>(shared_from_this()), direction, speed);
	moveComponent->init();
};
void Projectile::draw(sf::RenderWindow& window)
{
	if (inUse)
	{
		renderComponent->draw(window);
	}
	
};
void Projectile::update(float deltatime)
{
	if (inUse)
	{
		moveComponent->update(deltatime);
		renderComponent->update(deltatime);
	}
};