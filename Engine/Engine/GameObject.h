#pragma once
#include<memory>
#include<SFML/Graphics/Transformable.hpp>

class Component;
class GameObject : public sf::Transformable , public std::enable_shared_from_this<GameObject>		//Hilfsklasse, die dazu dient, std::shared_ptr-Instanzen aus "this" (dem rohen Zeiger auf ein Objekt) zu erstellen
{
public:
	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};		


	