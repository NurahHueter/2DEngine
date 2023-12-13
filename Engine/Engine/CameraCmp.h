#pragma once
#include "IRenderComponent.h"
#include<memory>
namespace mmt_gd
{
	class CameraCmp : public IRenderComponent
	{
	public:
		CameraCmp(GameObject& gameObject, sf::RenderWindow& renderWindow, sf::Vector2f size, GameObject& target)
			:IRenderComponent(gameObject, renderWindow), size(size), target(target) {};

		bool init() override;
		void update(float deltaTime) override;
		void draw() override;

		void rotate(float& degree);
		void zoom(float& zoom);
		void setSize(sf::Vector2f& size);
		void setViewPort(sf::FloatRect& viewPort);

		sf::Vector2f size;
		sf::View view;

		GameObject& target;
	};
};