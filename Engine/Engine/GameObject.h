#pragma once
#include<memory>
#include<SFML/Graphics/Transformable.hpp>

class Component;
class GameObject : public sf::Transformable
{
public:
	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};		


	