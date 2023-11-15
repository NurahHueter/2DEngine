#pragma once
#include"pch.h"
#include"Rocket2.h"
#include"RenderCmp.h"
#include"MoveCmp.h"
#include"InputManager.h"

void Rocket2::init()
{
	renderComponent = std::make_shared<RenderCmp>(std::weak_ptr<GameObject>(shared_from_this()), "../Assets/rocket.png", "rocket2");
	renderComponent->init();
	moveComponent = std::make_shared<MoveCmp>(std::weak_ptr<GameObject>(shared_from_this()), sf::Vector2f(0, 0), 200.f);
	moveComponent->init();
	this->setPosition(sf::Vector2f(300, 500));
};
void Rocket2::draw(sf::RenderWindow& window )
{
	
	// Konvertiere die Mausposition in die Spielkoordinaten

	if (InputManager::instance().isKeyDown("leftclick", 2))
	{
		// Holen Sie sich die aktuelle Mausposition im Fenster
		sf::Vector2f worldMousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		sf::Vector2f direction = worldMousePosition - this->getPosition();
		std::cout << worldMousePosition.x << " und " << worldMousePosition.y <<std::endl;

		// Setze die Richtung für die Bewegungskomponente
		moveComponent->setDirection(direction);
	}

	renderComponent->draw(window);

};
void Rocket2::update(float deltatime)
{
	moveComponent->update(deltatime);
	moveComponent->setDirection(sf::Vector2f(0, 0));
	renderComponent->update(deltatime);
};