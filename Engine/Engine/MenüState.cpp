#pragma once

#include "pch.h"
#include "GameState.h"
#include "CameraCmp.h"
#include "MapTile.h"
namespace mmt_gd
{
    void MenuState::init()
    {
       
        tson::Tileson t;
        const std::unique_ptr<tson::Map> map = t.parse(mapTile.m_resourcePath / "game.tmj");
        mapTile.loadMap(map);

        const auto& mapObj = std::make_shared<GameObject>("map");
        mapTile.getTiledLayer(*mapObj, map);

        mapObj->init();
        m_gameObjectManager.addGameObject(mapObj);

    }

    void MenuState::exit()
    {
        m_gameObjectManager.shutdown();
    }

    void MenuState::update(float deltaTime)
    {
        m_gameObjectManager.update(deltaTime);
    }

    void MenuState::draw(sf::RenderWindow& m_window)
    {
        m_window.clear({ 0, 0, 0 });

        m_gameObjectManager.draw();

        m_window.display();
    }
}