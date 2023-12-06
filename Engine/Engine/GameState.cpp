#pragma once

#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "CameraCmp.h"
#include "WindowManager.h"
#include "GameObject.h"
#include "RenderCmp.h"
#include "MoveCmp.h"
#include "MouseMoveCmp.h"


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

void MainState::init()
{
    //all AsstetsforTheState
    AssetManager::instance().LoadTexture("rocket", "../Assets/Hunter1-right.bmp");
    std::shared_ptr<sf::Texture> rocket_T = AssetManager::instance().m_Textures["rocket"];

    AssetManager::instance().LoadTexture("background", "../Assets/bg_space_seamless.png");
    std::shared_ptr<sf::Texture> background_T = AssetManager::instance().m_Textures["background"];

    assets.push_back("rocket");
    assets.push_back("background");

    // projectile
    
    //rocket_one -> mit WASD
    std::shared_ptr<GameObject> rocket_one = std::make_shared<GameObject>();
    std::shared_ptr<Component> renderRocket = std::make_shared<RenderCmp>("RenderRocket", rocket_one, rocket_T);
    std::shared_ptr<Component> moveRocket = std::make_shared<MoveCmp>("MoveRocket", rocket_one, sf::Vector2f(0, 0), 500.f);

    rocket_one->addComponent("RenderRocket" ,renderRocket);
    rocket_one->addComponent("MoveRocket",moveRocket);
    rocket_one->setPosition(sf::Vector2f(22, -5));

    //rocket_two -> mit Mouse
    std::shared_ptr<GameObject> rocket_two = std::make_shared<GameObject>();
    std::shared_ptr<Component> renderRocket_two = std::make_shared<RenderCmp>("RenderRocket", rocket_two, rocket_T);
    std::shared_ptr<Component> moveRocket_two = std::make_shared<MouseMoveCmp>("MoveRocket", rocket_two, sf::Vector2f(50, 50), 500.f);

    rocket_two->addComponent("RenderRocket", renderRocket_two);
    rocket_two->addComponent("MoveRocket", moveRocket_two);
    rocket_two->setPosition(sf::Vector2f(22, -5));

    //background
    std::shared_ptr<GameObject> background_one = std::make_shared<GameObject>();
    std::shared_ptr<GameObject> background_two = std::make_shared<GameObject>();

    std::shared_ptr<Component> render_background_one = std::make_shared<RenderCmp>("RenderSpace", background_one, background_T);
    std::shared_ptr<Component> render_background_two = std::make_shared<RenderCmp>("RenderSpace", background_one, background_T);

    background_one->addComponent("background_one", render_background_one);
    background_two->addComponent("background_two", render_background_two);

    //camera
    std::shared_ptr<GameObject> camera = std::make_shared<GameObject>();
    //set the camera in the center of the screen, if you dont do this the 0,0 point is in the middle 
    camera->setPosition(WindowManager::instance().m_window.getSize().x / 2, WindowManager::instance().m_window.getSize().y / 2);

    //set size of size from window
    std::shared_ptr<Component> cameraCmp = std::make_shared<CameraCmp>("camera", camera, sf::Vector2f(WindowManager::instance().m_window.getSize().x, WindowManager::instance().m_window.getSize().y));
    camera->addComponent("camera", cameraCmp);
 

    //add to map //wichtig auf reihenFolge achten -> wegen Draw
    gameObjects.insert(std::make_pair("background_one", background_one));
    gameObjects.insert(std::make_pair("background_two", background_two));
    gameObjects.insert(std::make_pair("rocket_one", rocket_one));
    gameObjects.insert(std::make_pair("rocket_two", rocket_two));
    gameObjects.insert(std::make_pair("camera", camera));

    //init all Components in all gameObjects
    for (auto& obj : gameObjects)
    {
        for (auto& cmp : obj.second->components)
        {
            cmp.second->init();
        }
    }

    //set position of second background after the first
    float width_texture = 0;
    auto it = background_one->components.find("background_one");
    if (it != background_one->components.end()) {
        if (auto temp = std::dynamic_pointer_cast<RenderCmp>(it->second))
        {
            width_texture = temp->sprite->getTextureRect().width;
        }
    }
    background_two->setPosition(sf::Vector2f(background_one->getPosition().x + width_texture, background_one->getPosition().y));
}


void MainState::exit()
{
    gameObjects.clear();
    
    std::vector<std::string>::iterator obj;
    for (obj = assets.begin(); obj < assets.end(); obj++)
    {
        AssetManager::instance().UnloadTexture(*obj);
    }
}

void MainState::update(float deltaTime)
{
    for (auto& obj : gameObjects) {
        obj.second->update(deltaTime);
    }
    
    //move camera
    auto it_cam = gameObjects.find("camera");
    if (it_cam != gameObjects.end()) 
    {
        it_cam->second->setPosition(sf::Vector2f(it_cam->second->getPosition().x +40.f * deltaTime, it_cam->second->getPosition().y));
            
        //switch backgrounds for endless loop
        auto it_bg1 = gameObjects.find("background_one");
        auto it_bg2 = gameObjects.find("background_two");
            if (it_bg1 != gameObjects.end() && it_bg2 != gameObjects.end()) {
                if ((it_cam->second->getPosition().x - WindowManager::instance().m_window.getSize().x / 2) >= it_bg2->second->getPosition().x)
                {
                    float width_texture = 0;
                    auto it = it_bg1->second->components.find("background_one");
                    if (it != it_bg1->second->components.end()) {
                        if (auto temp = std::dynamic_pointer_cast<RenderCmp>(it->second))
                        {
                            width_texture = temp->sprite->getTextureRect().width;
                            
                        }
                        switchCount % 2 ? it_bg1->second->setPosition(it_bg1->second->getPosition().x + width_texture, 0) : it_bg2->second->setPosition(it_bg2->second->getPosition().x + width_texture, 0);
                        switchCount++;
                    }
                }
            }
          //check if rockets are in camera view
            auto it_rocket_one = gameObjects.find("rocket_one");
            if (it_rocket_one->second->getPosition().x <= it_cam->second->getPosition().x - WindowManager::instance().m_window.getSize().x / 2)
                {
                    it_rocket_one->second->setPosition(it_cam->second->getPosition().x - WindowManager::instance().m_window.getSize().x / 2, it_rocket_one->second->getPosition().y);
                }
            auto it_rocket_two = gameObjects.find("rocket_two");
            if (it_rocket_two->second->getPosition().x <= it_cam->second->getPosition().x - WindowManager::instance().m_window.getSize().x / 2)
            {
                it_rocket_two->second->setPosition(it_cam->second->getPosition().x - WindowManager::instance().m_window.getSize().x / 2, it_rocket_two->second->getPosition().y);
            }

    }
}

void MainState::draw(sf::RenderWindow& m_window)
{
    m_window.clear({ 0, 0, 255 });

    for (auto& obj : gameObjects) {
        obj.second->draw(m_window);
    }

    m_window.display();
}
