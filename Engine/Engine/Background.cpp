#pragma once
#include "pch.h"
#include"Background.h"
#include"RenderComponent.h"

void Background::init()
{
	renderComponent = std::make_shared<RenderComponent>(this, "../Assets/Space.jpg", "Space");
	renderComponent->init();
};
void Background::draw(sf::RenderWindow& window)
{
	renderComponent->draw(window);
};