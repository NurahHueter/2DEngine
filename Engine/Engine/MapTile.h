#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <vector>
#include "tileson.hpp"
#include "IRenderComponent.h"
#include "Game.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "WindowManager.h"

class MapTile
{
public:
   

    using GameObjectPtr = std::shared_ptr<GameObject>;
    using TexturePtr = std::shared_ptr<sf::Texture>;
    using SpritePtr = std::shared_ptr<sf::Sprite>;

    void loadMap(const std::filesystem::path& filename, const sf::Vector2f& offset);
    void drawLayer(sf::RenderWindow& m_window, const std::vector<SpritePtr>& layer);

    sf::RenderWindow m_window;
    float m_fScrollOffset{};
    float m_fScrollOffsetPixelPrecise{};
    sf::RenderTexture m_offscreen;
    sf::Sprite m_offscreenSprite;

    std::unordered_map<std::string, TexturePtr> m_tileSetTexture;
    const std::filesystem::path m_resourcePath{ "Assets" };

    std::vector<std::vector<SpritePtr>> m_layers;
    std::unordered_map<std::string, GameObjectPtr> m_objects;
};


