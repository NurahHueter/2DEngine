// GameStateManager.cpp
#pragma once
#include "pch.h"
#include "GameStateManager.h"
#include "GameState.h"
namespace mmt_gd
{

    void GameStateManager::addState(std::string stateName, std::shared_ptr<GameState> state)
    {
        states[stateName] = state;
    };

    void GameStateManager::update(float delta) {
        currentState->update(delta);
    }

    void GameStateManager::draw() {
        currentState->draw();
       
    }

    void GameStateManager::setState(std::string stateName) {
        std::shared_ptr<GameState> state = states[stateName];

        if (state != currentState) {
            if (currentState != nullptr) {
                std::cout << "exit State" << std::endl;
                currentState->exit();
            }
            currentState = std::move(state);
            currentState->init();
        }
    }

    void GameStateManager::CloseGame()
    {
        currentState->exit();
        states.clear();
    }
}
