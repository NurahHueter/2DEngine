#pragma once
#include "pch.h"
#include "GameObject.h"
#include "CameraCmp.h"

void CameraCmp::init()
{
	if (std::shared_ptr<GameObject> tempP = gameObject.lock()) //check if Gameobject is nullptr
	{
		view.reset(sf::FloatRect(tempP->getPosition(), size));
	}
}
void CameraCmp::update(float deltaTime)
{
	if (std::shared_ptr<GameObject> tempP = gameObject.lock())
	{
		view.setCenter(tempP->getPosition());
	}
}

void CameraCmp::draw(sf::RenderWindow& window)
{
	window.setView(view);
};

void CameraCmp::rotate(float& degree)
{
	view.rotate(degree);
};

void CameraCmp::zoom(float& zoom)
{
	view.rotate(zoom);
};

void CameraCmp::setSize(sf::Vector2f& size)
{
	view.setSize(size);
};

void CameraCmp::setViewPort(sf::FloatRect& viewPort)
{
	view.setViewport(viewPort);
};