#pragma once
#include<memory>
#include<SFML/Graphics/Transformable.hpp>

class Component;
class GameObject : public sf::Transformable		//Hilfsklasse, die dazu dient, std::shared_ptr-Instanzen aus "this" (dem rohen Zeiger auf ein Objekt) zu erstellen
{
public:
	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	void addComponent( std::string,std::shared_ptr<Component> component);
	std::shared_ptr<Component> getComponent(std::string id);
	void deleteComponent(std::shared_ptr<Component> component);
	std::map< std::string, std::shared_ptr<Component>> components;

};		


	