#pragma once
#include "Component.h"
#include<memory>
class Sprite;
class Texture;
class RenderComponent : Component
{
public:                                                         
	RenderComponent(std::string textureFilePath, std::string textureName)
		: textureFilePath(textureFilePath), textureName(textureName) {};
	~RenderComponent();
	void init() override; 
	void update(float deltaTime) override {};
	void draw(sf::RenderWindow& window) override;
	
	std::string textureFilePath;
	std::string textureName;
	std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();	
};

                                                                                         \
