#pragma once
#include "IRenderComponent.h"
#include<memory>

class GameObject;
class CameraCmp final : public IRenderComponent
{
public:
	CameraCmp(GameObject& gameObject, sf::RenderWindow& renderWindow, sf::Vector2f size)
		:IRenderComponent(gameObject, renderWindow), size(size) {};

	bool init() override;
	void update(float deltaTime) override;
	void draw() override;

	void rotate(float& degree);
	void zoom(float& zoom);
	void setSize(sf::Vector2f& size);
	void setViewPort(sf::FloatRect& viewPort);

	sf::Vector2f size;
	sf::View view;
};