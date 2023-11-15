#pragma once
#include "pch.h"
#include"Background.h"
#include"RenderCmp.h"

void Background::init()
{
	renderComponent = std::make_shared<RenderCmp>(std::weak_ptr<GameObject>(shared_from_this()), "../Assets/Space.jpg", "Space");
	renderComponent->init();
	renderComponent2 = std::make_shared<RenderCmp>(std::weak_ptr<GameObject>(shared_from_this()), "../Assets/Space.jpg", "Space2");
	renderComponent2->init();

	renderComponent2->sprite->setPosition(sf::Vector2f(renderComponent->sprite->getPosition().x + renderComponent->sprite->getTextureRect().width, renderComponent->sprite->getPosition().y));
};
void Background::draw(sf::RenderWindow& window)
{
	renderComponent->draw(window);
	renderComponent2->draw(window);
};

void Background::swap(float check)
{
	//swithc die bilder, sodass ein endlessloop entsteht
	if (check >= renderComponent2->sprite->getPosition().x)
	{
		if (switchCount % 2)
		{
			renderComponent->sprite->setPosition(renderComponent->sprite->getPosition().x + renderComponent->sprite->getTextureRect().width, 0);			
		}
		else
		{
			renderComponent2->sprite->setPosition(renderComponent->sprite->getPosition().x + renderComponent->sprite->getTextureRect().width, 0);
		};
		switchCount++;
	}
};