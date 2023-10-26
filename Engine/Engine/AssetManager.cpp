#include "AssetManager.h"
#include <iostream>
#pragma once

void AssetManager::LoadTexture(std::string name, std::string filename) {
	sf::Texture texture;

	if (texture.loadFromFile(filename)) {
		this->Textures.insert(std::pair<std::string, sf::Texture>(name, texture));
	}
	else {
		std::cout << "Fehler beim Laden der Textur " << name << " aus der Datei " << filename << std::endl;
	}
}

void AssetManager::LoadSoundBuffer(std::string name, std::string filename) {
	sf::SoundBuffer sound;

	if (sound.loadFromFile(filename)) {
		this->SoundBuffer.insert(std::pair<std::string, sf::SoundBuffer>(name, sound));
	}
	else {
		std::cout << "Fehler beim Laden des Sounds " << name << " aus der Datei " << filename << std::endl;
	}
}

void AssetManager::LoadMusic(std::string name, std::string filename) {
	//sf::Music music;

	//if (music.openFromFile(filename)) {
	//	this->Music.insert(std::pair<std::string, sf::Music>(name, music));
	//}
	//else {
	//	std::cout << "Fehler beim Laden der Musik " << name << " aus der Datei " << filename << std::endl;
	//}
}

void AssetManager::LoadFont(std::string name, std::string filename) {
	sf::Font font;

	if (font.loadFromFile(filename)) {
		
		this->Font.insert(std::pair<std::string, sf::Font>(name, font));
	}
	else {
		std::cout << "Fehler beim Laden der Font " << name << " aus der Datei " << filename << std::endl;
	}

}


//this->Textures[name] = texture;

// Music loadFromFile??
// was ist besser? //this->Textures[name] = texture;
//					 this->Textures.insert(std::pair<std::string, sf::Texture>(name, texture));
// Was brauchen wir noch außer Manager?