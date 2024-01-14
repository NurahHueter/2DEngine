#include "pch.h"
#include "AssetManager.h"
#include "Game.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "CameraCmp.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SpriteRenderCmp.h"
#include "MoveCmp.h"
#include "MouseMoveCmp.h"
#include "RigidBodyCmp.h"
#include "BoxCollisionCmp.h"
#include "PhysicsManager.h"
namespace mmt_gd
{
    void MainState::init()
    {
        //map
        tson::Tileson t;
        const fs::path tileMapresourcePath = { "Assets" };
        const std::unique_ptr<tson::Map> map = t.parse(tileMapresourcePath / "game.tmj");
        mapTile.loadMap(map, tileMapresourcePath);

        const auto& mapObj = std::make_shared<GameObject>("map");
        mapTile.getTiledLayer(*mapObj, map);
        mapTile.getObjectLayer(map);
        mapObj->init();
        GameObjectManager::instance().addGameObject(mapObj);
    }

    void MainState::exit()
    {
        GameObjectManager::instance().shutdown();
        PhysicsManager::instance().shutdown();
        RenderManager::instance().shutdown();
    }

    void MainState::update(float deltaTime)
    {
        PhysicsManager::instance().update();
        GameObjectManager::instance().update(deltaTime);
    }

    void MainState::draw()
    {
        RenderManager::instance().getWindow().clear({0, 0, 0});

        RenderManager::instance().draw();
        RenderManager::instance().getWindow().display();
    }
}