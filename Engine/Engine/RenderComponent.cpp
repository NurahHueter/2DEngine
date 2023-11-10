#include"pch.h"
#include"RenderComponent.h"
#include"AssetManager.h"


void RenderComponent::init()
{
	AssetManager::instance().LoadTexture(textureName, textureFilePath);
	sprite->setTexture(*AssetManager::instance().m_Textures[textureName]);
}

void RenderComponent::draw()
{

}