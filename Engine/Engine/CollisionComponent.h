#pragma once
#include"Component.h"
#include<SFML/Graphics/RectangleShape.hpp>
#include<memory>
class CollisionComponent : Component
{
public:
	CollisionComponent()
	{};

	void init();
	void update(float deltetime);
	
	std::shared_ptr<RectangleShape> rectangle = 
};