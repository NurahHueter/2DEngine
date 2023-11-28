#pragma once
#include "Component.h"
#include<memory>
class Sprite;
class Texture;
class GameObject;
class RenderCmp : public Component
{
public:                                                         
	RenderCmp(std::weak_ptr<GameObject> gameObject,std::string textureFilePath, std::string textureName)
		: Component(id), gameObject(gameObject), textureFilePath(textureFilePath), textureName(textureName) {};
	~RenderCmp() {};
	virtual void init() override; 
	virtual void update(float deltaTime) override;
	virtual void draw(sf::RenderWindow& window) override;
	
	std::weak_ptr<GameObject> gameObject;
	std::string textureFilePath;
	std::string textureName;
	std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
	
};

                                                                                         \
