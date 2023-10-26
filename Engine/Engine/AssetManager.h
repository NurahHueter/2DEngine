#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <map>
struct AssetManager
{

	static
		AssetManager &
		instance()
	{
		static AssetManager s;
		return s;
	} // instance

	AssetManager(const AssetManager&) = delete;
	AssetManager& operator = (const AssetManager&) = delete;

	std::map<std::string, sf::Texture> Textures {};							//Maps (dictionarys) erstellen
	std::map<std::string, sf::SoundBuffer> SoundBuffer {};
	std::map<std::string, sf::Music> Music {};
	std::map<std::string, sf::Font> Font {};
	void LoadTexture(std::string name, std::string filename);
	void LoadSoundBuffer(std::string name, std::string filename);
	void LoadMusic(std::string name, std::string filename);
	void LoadFont(std::string name, std::string filename);

private:

	AssetManager() 
	{
		
	}
	~AssetManager() {}

};