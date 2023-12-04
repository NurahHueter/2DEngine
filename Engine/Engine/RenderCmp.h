#pragma once
#include "Component.h"
#include<memory>
class Sprite;
class Texture;
class GameObject;
class RenderCmp : public Component, public std::enable_shared_from_this<RenderCmp>
{
public:                                                         
	RenderCmp(std::string id,std::weak_ptr<GameObject> gameObject, std::weak_ptr<sf::Texture> p_texture)
		: Component(id), gameObject(gameObject), p_texture(p_texture) {};
	~RenderCmp() {};
	virtual void init() override; 
	virtual void update(float deltaTime) override;
	virtual void draw(sf::RenderWindow& window) override;
	
	std::weak_ptr<GameObject> gameObject;
	std::string id;
	std::weak_ptr<sf::Texture> p_texture;
	std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
};

                                                                                         \
