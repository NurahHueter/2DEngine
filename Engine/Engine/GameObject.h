#pragma once
#include "All_Includes.h"

namespace sf {

class GameObject : public Transformable 
{
	virtual void Initialize()=0;
	virtual void Update(float deltaTime)=0;
	virtual void Draw(RenderWindow window)=0;
};		
}

