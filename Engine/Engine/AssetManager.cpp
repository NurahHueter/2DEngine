#include "AssetManager.h"
#include <iostream>
#pragma once

void AssetManager::LoadTexture(std::string name, std::string filename) {
	
	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();

	if (texture->loadFromFile(filename)) {
		this->m_Textures[name] = texture;
	}
	else {
		std::cout << "Fehler beim Laden der Textur " << name << " aus der Datei " << filename << std::endl;
	}
}

void AssetManager::LoadSoundBuffer(std::string name, std::string filename) {
	
	std::shared_ptr<sf::SoundBuffer> sound = std::make_shared<sf::SoundBuffer>();

	if (sound->loadFromFile(filename)) {
		this->m_SoundBuffer[name] =sound;
	}
	else {
		std::cout << "Fehler beim Laden des Sounds " << name << " aus der Datei " << filename << std::endl;
	}
}

void AssetManager::LoadMusic(std::string name, std::string filename) {
	std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();

	if (music->openFromFile(filename)) {
		this->m_Music[name] = music;
	}
	else {
		std::cout << "Fehler beim Laden der Musik " << name << " aus der Datei " << filename << std::endl;
	}
}

void AssetManager::LoadFont(std::string name, std::string filename) {	
	std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();

	if (font->loadFromFile(filename)) {
		this->m_Font[name] = font;
	}
	else {
		std::cout << "Fehler beim Laden der Font " << name << " aus der Datei " << filename << std::endl;
	}

}


//this->Textures[name] = texture;

// Music loadFromFile??
// was ist besser? //this->Textures[name] = texture;
//					 this->Textures.insert(std::pair<std::string, sf::Texture>(name, texture));
// Was brauchen wir noch auﬂer Manager?