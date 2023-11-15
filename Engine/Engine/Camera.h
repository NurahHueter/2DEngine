#pragma once
#include"GameObject.h"
class Camera : GameObject
{
	Camera(sf::Vector2f position, sf::Vector2f size) 
	{
		view.reset(sf::FloatRect(position, size));
	};

	void init() override {};
	void draw(sf::RenderWindow& window) override;
	void update(float deltatime) override {};
	void rotate(float degree);
	void zoom(float zoom);
	void move(sf::Vector2f offset);
	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	void setViewPort(sf::FloatRect viewPort);

private:
	sf::View view;
};