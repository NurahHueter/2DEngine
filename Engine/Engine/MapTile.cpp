#pragma once
#include "pch.h"
#include "tileson.hpp"
#include "AssetManager.h"
#include "TileLayerCmp.h"
#include "MapTile.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "ObjectFactory.h"

namespace mmt_gd
{

	using namespace sf;
	using namespace std;
	std::vector<std::vector<int>> MapTile::m_LayerKachel;
	void MapTile::loadMap(const std::unique_ptr<tson::Map>& map, const fs::path resourcePath)
	{

		const int numRows = 50;
		const int numCols = 90;

		auto layerData0 = map->getLayers()[0].getData();
		auto layerData1 = map->getLayers()[1].getData();
		auto layerData2 = map->getLayers()[2].getData();

		m_LayerKachel.reserve(numRows);
		//TODO -> Eine reihe Polster für das Flugzeug

		for (int i = 0; i < numRows; ++i) {
			m_LayerKachel.emplace_back(); // Fügt eine leere Zeile hinzu
			m_LayerKachel[i].reserve(numCols);

			for (int j = 0; j < numCols; ++j) {
				// Überprüfe, ob entweder layerData1 oder layerData2 an dieser Position nicht null ist
				if (layerData1[i * numCols + j] != 0 || layerData2[i * numCols + j] != 0) {
					m_LayerKachel[i].push_back(9);
				}
				else {
					m_LayerKachel[i].push_back(1);
				}
			}
		}
		for (int i = 0; i < numRows; ++i) {
			for (int j = 0; j < numCols; ++j) {
				std::cout << m_LayerKachel[i][j] << " ";
			}
			std::cout << std::endl;
		}

		if (map->getStatus() == tson::ParseStatus::OK)
		{
			err() << "Load tile map with size: " << map->getSize().x << ", "
				<< map->getSize().y << " and tile size: " << map->getTileSize().x
				<< ", " << map->getTileSize().y << std::endl;

			for (auto& tileSet : map->getTilesets())
			{
				fs::path tileSetPath = tileSet.getImage().u8string();

				AssetManager::instance().LoadTexture(tileSet.getName(), (resourcePath / tileSetPath).string());
				if (!AssetManager::instance().m_Textures[tileSet.getName()])
				{
					err() << "Could not load texture " << resourcePath / tileSetPath << endl;
				}
			}
		}
		else
		{
			std::cout << "Parse error: " << map->getStatusMessage() << std::endl;
		}
	}

	void MapTile::getObjectLayer(const std::unique_ptr<tson::Map>& map)
	{
		for (auto group : map->getLayers())
		 {
 			// go over all objects per layer
 			for (auto object : group.getObjects())
 			{
				ObjectFactory::processTsonObject(object, group);
 			}
		 }
	}


	void MapTile::getTiledLayer(GameObject& gameObject, const std::unique_ptr<tson::Map>& map)
	{
		std::vector<TileLayer> layers;
		layers.resize(map->getLayers().size());

		for (int layerIdx = 0; layerIdx < static_cast<int>(map->getLayers().size()); layerIdx++)
		{
			auto layer = map->getLayers()[layerIdx];

			layers[layerIdx].m_name = layer.getName();
			layers[layerIdx].m_dimension = Vector2i(layer.getSize().x, layer.getSize().y);
			layers[layerIdx].m_tileSize = Vector2i(map->getTileSize().x, map->getTileSize().y);


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
				const auto& texture = *AssetManager::instance().m_Textures[tileSet->getName()];
				
				// calculate position of tile
				Vector2f position;
				position.x = i % layer.getSize().x * static_cast<float>(tileSize.x);
				position.y = i / layer.getSize().x * static_cast<float>(tileSize.y);
				//position += offset;

				// number of tiles in tile set texture (horizontally)
				const int tileCountX = texture.getSize().x / tileSize.x;

				// calculate 2d idx of tile in tile set texture
				const int idx = gid - tileSet->getFirstgid();
				const int idxX = idx % tileCountX;
				const int idxY = idx / tileCountX;
				
				// calculate source area of tile in tile set texture
				IntRect source(idxX * tileSize.x, idxY * tileSize.y, tileSize.x, tileSize.y);

				//add Tile Sprite
				const auto sprite = std::make_shared<sf::Sprite>();
				sprite->setTexture(texture);
				sprite->setTextureRect(source);
				sprite->setPosition(position.x, position.y);
				layers[layerIdx].m_tiles.push_back({ i, sprite });
			}
		}
		int count = 0;
		for (auto& layer : layers)
		{
			RenderManager::instance().addLayer(layer.m_name, count);
			const auto& tileLayer = std::make_shared<TileLayerCmp>(
				gameObject,
				RenderManager::instance().getWindow(),
				layer);
			RenderManager::instance().addCompToLayer(layer.m_name, tileLayer);
			gameObject.addComponent(tileLayer);
			count++;
		}
	}
}


	