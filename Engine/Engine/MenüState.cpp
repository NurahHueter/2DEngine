#pragma once

#include "pch.h"
#include "GameState.h"
#include "CameraCmp.h"
#include "MapTile.h"
namespace mmt_gd
{
    void MenuState::init()
    {
        std::cout << "init MenuState" << std::endl;

    }

    void MenuState::exit()
    {
        GameObjectManager::instance().shutdown();
    }

    void MenuState::update(float deltaTime)
    {
        GameObjectManager::instance().update(deltaTime);
    }

    void MenuState::draw()
    {
        RenderManager::instance().getWindow().clear({ 0, 0, 0 });

        RenderManager::instance().getWindow().display();
    }
}