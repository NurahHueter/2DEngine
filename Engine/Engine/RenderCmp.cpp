#include"pch.h"
#include"RenderCmp.h"
#include "GameObject.h"
#include"AssetManager.h"

RenderCmp::~RenderCmp()
{
	AssetManager::instance().UnloadTexture(textureName);
}
void RenderCmp::init()
{
	AssetManager::instance().LoadTexture(textureName, textureFilePath);
	sprite->setTexture(*AssetManager::instance().m_Textures[textureName]);
	/*sprite->setScale(scale);*/
	/*sprite->setOrigin(sprite->getTextureRect() / 2.f, sprite->getTextureRect() / 2.f);*/ 
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