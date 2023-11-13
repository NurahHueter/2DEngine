#include"pch.h"
#include"RenderComponent.h"
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
}

void RenderComponent::draw(sf::RenderWindow& window)
{
	window.draw(*sprite);
}