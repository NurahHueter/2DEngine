// GameStateManager.cpp
#pragma once
#include "pch.h"
#include "GameStateManager.h"
#include "GameState.h"
namespace mmt_gd
{

    void GameStateManager::Init()
    {
        auto menu = std::make_shared<MenuState>();
        auto main = std::make_shared<MainState>();

        states["MenuState"] = menu;
        states["MainState"] = main;
    }

    void GameStateManager::update(float delta) {
        //std::cout << "update State" <<  std::endl;
        currentState->update(delta);
    }

    void GameStateManager::draw(sf::RenderWindow& m_window) {
        // std::cout << "draw State" << std::endl;
        currentState->draw(m_window);

    }

    void GameStateManager::setState(std::string stateName) {
        std::shared_ptr<GameState> state = states[stateName];

        if (state != currentState) {
            if (currentState != nullptr) {
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
