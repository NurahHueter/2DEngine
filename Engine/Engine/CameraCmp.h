#pragma once
#include "Component.h"
#include<memory>

class GameObject;
class CameraCmp : public Component
{
public:
	CameraCmp(std::string id, std::weak_ptr<GameObject> gameObject, sf::Vector2f size)
		:Component(id), gameObject(gameObject), size(size) {}

	void init() override;
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void rotate(float& degree);
	void zoom(float& zoom);
	void setSize(sf::Vector2f& size);
	void setViewPort(sf::FloatRect& viewPort);

	std::weak_ptr<GameObject> gameObject;
	sf::Vector2f size;
	sf::View view;
};