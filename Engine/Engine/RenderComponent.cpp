#include"pch.h"
#include"RenderComponent.h"
#include "GameObject.h"
#include"AssetManager.h"

RenderComponent::~RenderComponent()
{
	AssetManager::instance().UnloadTexture(textureName);
}
void RenderComponent::init()
{
	AssetManager::instance().LoadTexture(textureName, textureFilePath);
	sprite->setTexture(*AssetManager::instance().m_Textures[textureName]);
	/*sprite->setScale(scale);*/
	/*sprite->setOrigin(sprite->getTextureRect() / 2.f, sprite->getTextureRect() / 2.f);*/ 
}

void RenderComponent::update(float deltetime) 
{
	if (std::shared_ptr<GameObject> tempP = gameObject.lock()) //check if Gameobject is nullptr
	{
		sprite->setPosition(tempP->getPosition());
	}
	
}

void RenderComponent::draw(sf::RenderWindow& window)
{
	window.draw(*sprite);
}