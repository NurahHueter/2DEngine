#pragma once
#include "pch.h"
#include "Camera.h"

void Camera::draw(sf::RenderWindow& window) 
{
	window.setView(view);
};
void Camera::rotate(float degree) 
{
	view.rotate(degree);
};
void Camera::zoom(float zoom)
{
	view.rotate(zoom);
};
void Camera::move(sf::Vector2f offset)
{
	view.move(offset);
	this->setPosition(this->getPosition() + offset);
};

void Camera::setViewPosition(sf::Vector2f position) 
{
	view.setCenter(position);
	this->setPosition(position);
};

sf::Vector2f Camera::getViewPosition()
{
	return this->getPosition();
};
void Camera::setSize(sf::Vector2f size) 
{
	view.setSize(size);
};
void Camera::setViewPort(sf::FloatRect viewPort)
{
	view.setViewport(viewPort);
};