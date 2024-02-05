#pragma once

#include "pch.h"
#include "GameState.h"
#include "CameraCmp.h"
#include "Assetmanager.h"
#include "MapTile.h"

namespace mmt_gd
{
    void MenuState::init()
    {
        AssetManager::instance().LoadFont("font","../Engine/Assets/SpaceShip/arial.ttf");
        const auto camerGo = std::make_shared<GameObject>("camera");
        const auto cameraCmp = std::make_shared<CameraCmp>(*camerGo,
            RenderManager::instance().getWindow(),
            sf::Vector2f(RenderManager::instance().getWindow().getSize().x / 2.0f,
                RenderManager::instance().getWindow().getSize().y / 2.0f));
        cameraCmp->setCenter(sf::Vector2f(RenderManager::instance().getWindow().getSize().x / 2, RenderManager::instance().getWindow().getSize().y / 2));
        camerGo->addComponent(cameraCmp);
        RenderManager::instance().addLayer("camera", 1);
        RenderManager::instance().addCompToLayer("camera", cameraCmp);
    }

    void MenuState::exit()
    {
        GameObjectManager::instance().shutdown();
        RenderManager::instance().shutdown();
    }

    void MenuState::update(float deltaTime)
    {
        GameObjectManager::instance().update(deltaTime);
    }

    void MenuState::draw()
    {
        RenderManager::instance().getWindow().clear({ 0, 0, 0 });
        sf::Text text;
        text.setFont(*AssetManager::instance().m_Font["font"]); 
        text.setString("Press 2 to start the game, press 1 to come back to Startscreen");
        text.setCharacterSize(24); 
        text.setFillColor(sf::Color::White);

        float x = (RenderManager::instance().getWindow().getView().getSize().x / 2);
        float y = (RenderManager::instance().getWindow().getView().getSize().y / 3);
        text.setPosition(x, y);
        RenderManager::instance().getWindow().draw(text);
        RenderManager::instance().draw();
        RenderManager::instance().getWindow().display();
    }
}