#pragma once
#include<memory>
#include<SFML/Graphics/Transformable.hpp>

class Component;
class GameObject : public sf::Transformable		
{
public:
	void init();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	void addComponent( std::string,std::shared_ptr<Component> component);
	std::shared_ptr<Component> getComponent(std::string id);
	void deleteComponent(std::shared_ptr<Component> component);

	std::map< std::string, std::shared_ptr<Component>> components;

};		


	