#pragma once
#include "pch.h"
#include "tileson.hpp"
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "WindowManager.h"
#include "MapTile.h"
#include "GameObject.h"
namespace mmt_gd
{

	using namespace sf;
	using namespace std;

	void MapTile::loadMap(const fs::path& filename, const Vector2f& offset)
	{
		tson::Tileson t;
		const std::unique_ptr<tson::Map> map = t.parse(filename);

		if (map->getStatus() == tson::ParseStatus::OK)
		{
			err() << "Load tile map with size: " << map->getSize().x << ", "
				<< map->getSize().y << " and tile size: " << map->getTileSize().x
				<< ", " << map->getTileSize().y << std::endl;

			for (auto& tileSet : map->getTilesets())
			{
				fs::path tileSetPath = tileSet.getImage().u8string();

				const auto texture = make_shared<Texture>();
				if (!texture->loadFromFile((m_resourcePath / tileSetPath).string()))
				{
					err() << "Could not load texture " << m_resourcePath / tileSetPath << endl;
				}
				m_tileSetTexture[tileSet.getName()] = texture;
			}
		}
		else
		{
			std::cout << "Parse error: " << map->getStatusMessage() << std::endl;
		}

		// go through all layers
		m_layers.resize(map->getLayers().size());
		cout << m_layers.size() << endl;			// es gibt 5 layer
		for (int layerIdx = 0; layerIdx < static_cast<int>(map->getLayers().size()); layerIdx++)
		{
			auto layer = map->getLayers()[layerIdx];
			err() << "Load layer: " << layer.getName() << " with width: "
				<< layer.getSize().x << " and height: " << layer.getSize().y << std::endl;

			const int size = layer.getSize().x * layer.getSize().y;

			// iterate over all elements/tiles in the layer
			for (int i = 0; i < size; i++)
			{
				const auto gid = layer.getData()[i];

				if (gid == 0)
				{
					// 0 means there is no tile at this position.
					continue;
				}

				// get tile set for tile and allocate the corresponding tileSet texture
				const auto* const tileSet = map->getTilesetByGid(gid);
				const Vector2i tileSize(map->getTileSize().x, map->getTileSize().y);
				Texture& texture = *m_tileSetTexture[tileSet->getName()];

				// calculate position of tile
				Vector2f position;
				position.x = i % layer.getSize().x * static_cast<float>(tileSize.x);
				position.y = i / layer.getSize().x * static_cast<float>(tileSize.y);
				position += offset;

				// number of tiles in tile set texture (horizontally)
				const int tileCountX = texture.getSize().x / tileSize.x;

				// calculate 2d idx of tile in tile set texture
				const int idx = gid - tileSet->getFirstgid();
				const int idxX = idx % tileCountX;
				const int idxY = idx / tileCountX;

				// calculate source area of tile in tile set texture
				IntRect source(idxX * tileSize.x, idxY * tileSize.y, tileSize.x, tileSize.y);

				// IMPORTANT: the tiles of the map are loaded here and put into layers as defined 
				// in the Tiled editor. The m_layers vector contains vectors of tile sprites, 
				// i.e., one vector of tile sprites for each layer. you can assign such a vector
				// to a TileLayerComponent, which is managed by the RenderManager. The RenderManager
				// takes care of rendering TileLayerComponents in the correct order 
				// (foreground, background, ...)			

				// create tile (Sprite) and put it into the appropriate layer.
				auto sprite = make_shared<Sprite>();
				sprite->setTexture(texture);
				sprite->setTextureRect(source);
				sprite->setPosition(position.x, position.y);

				m_layers[layerIdx].push_back(sprite);
			}
		}


		//// IMPORTANT: this is the second important loop. Here the game objects defined in the 
		//// Tiled editor are loaded (object layer). These game objects can easily be converted
		//// to your GameObjects used in-game. Helper functions help you structure your code, e.g.,
		//// createEnemy, createPlayer, createTreasureChest, ...
		//// These helper functions parse the information and create the correct GameObjects and Components
		//// for the GameObjects. 
		//// Ideally the GameStates do not contain any object generation code anymore. Objects are loaded
		//// from the Tiled editor file, i.e., have been placed in the Tiled editor.

	//	//// go through all object layers

		for (auto group : map->getLayers())
		{

			// go over all objects per layer
			for (auto object : group.getObjects())
			{
				Vector2f position(object.getPosition().x, object.getPosition().y);
				position += offset;

				// example to get a texture rectangle for a sprite
				FloatRect bounds(position.x, position.y, object.getSize().x, object.getSize().y);
				// TODO: check out game.tmj and there the content contained within <object group name="Object Layer 1">
				// there you can see the properties that you can parse, that should help you set up the sprites

				cout << object.getName() << endl; //name
				cout << object.getType() << endl; //classe	
				cout << object.getPosition().x << object.getPosition().y << endl;
				cout << object.getSize().x << object.getSize().y << endl;

				// gibt die punkte und den Typ der objekte aus -> BoundingBox,Sprite,...


				// TODO check data of object (position, type, etc.) 
				// type can be used to check for type of component that needs to be created.
				// In the exercise it is a GameObject by itself, in the assignments/engine 
				// think about configuring components for a GameObject.

				// TODO use data to initialize a sprite (texture rect, position, texture name, game object id...)

				if (object.getType() == "Sprite")
				{
					// IMPORTANT: a very simple sprite GameObject is created here. for your
					// assignment use the component-based architecture (e.g., GameObject + SpriteRenderComponent)
					const auto sprite = loadSprite(object);
					m_objects[object.getName()] = sprite;
				}
			}
		}
	}
	std::shared_ptr<MapTile::GameObject> MapTile::loadSprite(tson::Object& object)
	{
		auto gameObject = make_shared<GameObject>();

		IntRect textureRect{};
		textureRect.width = object.getSize().x;
		textureRect.height = object.getSize().y;

		// IMPORTANT: note how custom attributes (object->properties) created 
		// in the Tiled editor are parsed and used to initialize data for Components and
		// GameObjects.	
		// also note again: the GameObject is simplified for this example. A SpriteComponent should
		// be created instead.
		for (const auto* const property : object.getProperties().get())					//properties sind die unterklassen vom Sprite
		{
			cout << property->getName() << endl;
			auto name = property->getName();
			if (name == "Texture" &&
				!gameObject->m_texture.loadFromFile((m_resourcePath / std::any_cast<string>(property->getValue())).string()))
			{
				err() << "loadSprite: Could not load texture for sprite: " <<
					m_resourcePath / std::any_cast<string>(property->getValue()) << endl;
			}
			else if (name == "TextureRectLeft")	//wo f�ngt das sprite an
			{
				textureRect.left = std::any_cast<int>(property->getValue())+2;
			}
			else if (name == "TextureRectTop")
			{
				textureRect.top = std::any_cast<int>(property->getValue())+2;
			}
		}
		gameObject->m_sprite.setTexture(gameObject->m_texture);
		gameObject->m_sprite.setTextureRect(textureRect);
		gameObject->m_sprite.setPosition(object.getPosition().x, object.getPosition().y);

		cout << object.getPosition().x << object.getPosition().y << endl;
		cout << textureRect.top << textureRect.left << endl;
		return gameObject;
	}
	void MapTile::drawLayer(sf::RenderWindow& m_window, const std::vector<shared_ptr<sf::Sprite>>& layer)
	{
		for (const auto& sprite : layer)
		{
			m_window.draw(*sprite);
		}
	}

}


	