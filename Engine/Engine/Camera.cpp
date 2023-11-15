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
};
void Camera::setPosition(sf::Vector2f position) 
{
	view.setCenter(position);
};
void Camera::setSize(sf::Vector2f size) 
{
	view.setSize(size);
};
void Camera::setViewPort(sf::FloatRect viewPort)
{
	view.setViewport(viewPort);
};