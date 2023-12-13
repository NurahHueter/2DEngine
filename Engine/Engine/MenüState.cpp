#pragma once

#include "pch.h"
#include "GameState.h"
namespace mmt_gd
{
    void MenuState::init()
    {
        mapTile.loadMap(mapTile.m_resourcePath / "game.tmj", sf::Vector2f());

    }

    void MenuState::exit()
    {
        // Leere die Layer-Vektoren in der MapTile-Instanz
        mapTile.m_layers.clear();

        // Leere die Textur-Map in der MapTile-Instanz
        mapTile.m_tileSetTexture.clear();

        std::cout << "Tiled cleared" << std::endl;
    }

    void MenuState::update(float deltaTime)
    {
    }

    void MenuState::draw(sf::RenderWindow& m_window)
    {
        m_window.clear({ 0, 0, 0 });

        mapTile.drawLayer(m_window, mapTile.m_layers[0]); // Floor
        mapTile.drawLayer(m_window, mapTile.m_layers[1]); // Background

        m_window.display();
    }
}