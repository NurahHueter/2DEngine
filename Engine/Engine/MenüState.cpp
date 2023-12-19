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
        m_gameObjectManager.shutdown();
    }

    void MenuState::update(float deltaTime)
    {
        m_gameObjectManager.update(deltaTime);
    }

    void MenuState::draw()
    {
        m_window.clear({ 0, 0, 0 });

        m_window.display();
    }
}