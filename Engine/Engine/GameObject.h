#pragma once
#include"pch.h"

class Component;
class GameObject 
{
public:
	void init();
	void update(float deltaTime);
	void addComponent(Component component);

	std::vector<std::unique_ptr<Component>> components;	
};		


	