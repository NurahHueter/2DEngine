#include "GameState.h"
#include "AssetManager.h"
#include "pch.h"

void MenuState::init()  
{
	int status = MENU_STATE;
};

void MenuState::exit()  
{
};

void MenuState::update(float deltaTime) 
{
};

void MenuState::render()
{
};



void MainState::init()
{

	AssetManager::instance().LoadTexture("crystal", "../Assets/crystal.png");
	AssetManager::instance().LoadSoundBuffer("coolerSound", "../Assets/completeSound.wav");
	AssetManager::instance().LoadMusic("cooleMusik", "../Assets/musicTrack.ogg");

	sprite.setTexture(*AssetManager::instance().m_Textures["crystal"]);
};

void MainState::exit()
{
};

void MainState::update(float deltaTime)
{
};

void MainState::render() {};