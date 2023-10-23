#pragma once
// Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AssetManager.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

int main()
{
    //std::cout << "Hello World!\n";

	AssetManager& assetManager = AssetManager::instance();

    assetManager.LoadTexture("test", "C:/FH/3.Semester/beste-engine/Engine-C#/Assets/crystal.png");
    //window.display(assetManager.Textures("test"));

	// Annahme: Du hast bereits ein SFML-Fenster erstellt und es als 'window' benannt.
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");


	// Anzeigen der Textur auf dem Fenster:
	if (assetManager.Textures.find("test") != assetManager.Textures.end()) {
		sf::Sprite sprite(assetManager.Textures["test"]);
		
		while (true)
		{
			window.clear();
			window.draw(sprite);
			window.display();
		}
		
	}
	else {
		std::cerr << "Textur 'test' nicht im Asset Manager gefunden." << std::endl;
	}
}

