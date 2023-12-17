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
#include "WindowManager.h"
#include <SFML/Graphics/Texture.hpp>
namespace mmt_gd
{
    
    class MapTile
    {
    public:
		struct GameObject
		{
			sf::Texture m_texture;
			sf::Sprite m_sprite;
		};
       
        void loadMap(const std::filesystem::path& filename, const sf::Vector2f& offset);
		std::shared_ptr<GameObject> loadSprite(tson::Object& object);
        void drawLayer(sf::RenderWindow& m_window, const std::vector<std::shared_ptr<sf::Sprite>>& layer);

        sf::RenderWindow m_window;
        float m_fScrollOffset{};
        float m_fScrollOffsetPixelPrecise{};
        sf::RenderTexture m_offscreen;
        sf::Sprite m_offscreenSprite;

        std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_tileSetTexture;
   

        std::vector<std::vector<std::shared_ptr<sf::Sprite>>> m_layers;
        std::unordered_map<std::string, std::shared_ptr<GameObject>> m_objects;

        const fs::path m_resourcePath{ "Assets" };

    };



}
