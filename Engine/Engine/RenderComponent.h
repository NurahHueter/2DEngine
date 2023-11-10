#pragma once
#include "Component.h"
#include"pch.h"
class Sprite;
class Texture;
class RenderComponent : Component
{
public:
	RenderComponent(std::string&& textureFilePath, std::string textureName)
		: Component("RenderComponent"), textureFilePath(textureFilePath), textureName(textureName) {}

	~RenderComponent()
	{
		AssetManager::instance().UnloadTexture(textureName);
	}

	void init() override; 
	void draw(sf::RenderWindow& window) override;

private:
	std::string textureFilePath;
	std::string textureName;
	std::shared_ptr<sf::Sprite> sprite;
	std::shared_ptr<sf::Texture> texture; 
};