#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <vector>
#include "tileson.hpp"
#include "IRenderComponent.h"
#include "Game.h"
#include "GameObject.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "SpriteRenderCmp.h"
#include <SFML/Graphics/Texture.hpp>
namespace mmt_gd
{
    
    class MapTile
    {
    public:
 
       void loadMap(const std::unique_ptr<tson::Map>& map);
		/*std::shared_ptr<SpriteRenderCmp> loadSprite(tson::Object& object);*/

       void getTiledLayer(GameObject& gameObject, const std::unique_ptr<tson::Map>& map, sf::RenderWindow& window, RenderManager& renderManager);

       void getObjectLayer(const std::unique_ptr<tson::Map>& map, RenderManager& renderManager, GameObjectManager& gameObjectManager);

        const fs::path m_resourcePath{ "Assets" };

    };



}
