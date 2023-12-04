#pragma once
#include"pch.h"
#include"RenderCmp.h"
#include "GameObject.h"
#include"AssetManager.h"


//RenderCmp::~RenderCmp()
//{
//	AssetManager::instance().UnloadTexture(textureName);
//}
void RenderCmp::init()
{
	if (std::shared_ptr<sf::Texture> tempP = p_texture.lock()) //check if Gameobject is nullptr
	{
		sprite->setTexture(*tempP);
	}
}

void RenderCmp::update(float deltetime)
{
	if (std::shared_ptr<GameObject> tempP = gameObject.lock()) //check if Gameobject is nullptr
	{
		sprite->setPosition(tempP->getPosition());
	}
	
}

void RenderCmp::draw(sf::RenderWindow& window)
{
	window.draw(*sprite);
}