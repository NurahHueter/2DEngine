#pragma once
#include"GameObject.h"
class Camera : public GameObject
{
public:
	Camera(sf::Vector2f position, sf::Vector2f size) 
	{
		view.reset(sf::FloatRect(position, size));
		this->setPosition(position);
	};

	void init() override {};
	void draw(sf::RenderWindow& window) override;
	void update(float deltatime) override {};
	void rotate(float degree);
	void zoom(float zoom);
	void move(sf::Vector2f offset);
	void setViewPosition(sf::Vector2f position);
	sf::Vector2f getViewPosition();
	void setSize(sf::Vector2f size);
	void setViewPort(sf::FloatRect viewPort);
	sf::View view;
};