#pragma once
#include "pch.h"
#include"Background.h"
#include"RenderComponent.h"

void Background::init()
{
	renderComponent = std::make_shared<RenderComponent>("../Assets/Space.jpg", "Space");
	renderComponent->init();
};
void Background::draw(sf::RenderWindow& window)
{
	renderComponent->draw(window);
};