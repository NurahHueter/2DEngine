#pragma once
#include <SFML/Graphics/Transformable.hpp>
class RenderWindow;

class GameObject 
{
	virtual void Initialize()=0;
	virtual void Update(float deltaTime)=0;	
};		


	