#pragma once
#include "GameStateManager.h"
#include "GameState.h"
#include "pch.h"

void GameStateManager::Init()
{
	auto menu = std::unique_ptr<MenuState>();
	std::unique_ptr<GameState> main = std::unique_ptr<MainState>();

	states["MenuState"] = std::move(menu);
	states["MainState"] = std::move(main);
}

void GameStateManager::update(float delta)
{
	currentState->update(delta);
}

void GameStateManager::draw()
{
	currentState->draw();
}

void GameStateManager::setState(std::string stateName) {
	GameState* state = states[stateName];
	if (state != currentState) {
		if (currentState != nullptr) {
			currentState->exit();
		}
		currentState = state;
		currentState->init(this);
	}
}