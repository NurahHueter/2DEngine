#pragma once
#include"Component.h"
#include<memory>
class Sprite;
class RectangleShape;
class CollisionComponent : Component
{
public:
	CollisionComponent(Sprite& sprite) :
		sprite(sprite) {};
	void init();
	void update(float deltetime);
	Sprite& sprite; 
	std::shared_ptr<RectangleShape> rectangle;
};