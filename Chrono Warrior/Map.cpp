#include "stdafx.h"
#include "Map.h"

#include "Tile.h"
#include "FieldUnit.h"

#include <cassert>

namespace CW
{
	Map::Map()
	{
	}
	Map::~Map()
	{

	}

	void Map::Initialize()
	{
		std::string xmlName = "Stage/stage1.xml";
		tinyxml2::XMLDocument doc;
		doc.LoadFile(xmlName.c_str());

		if (doc.Error() == true)
		{
			assert(false);
			return;
		}

		auto* root = doc.RootElement();
		auto* stage = root->FirstChildElement("size");
		auto* map = stage->NextSiblingElement("map");

		mWidth = stage->IntAttribute("width");
		mHeight = stage->IntAttribute("height");
		std::string mapRawData = map->GetText();

		for (int y = 0; y < mWidth; ++y)
		{
			for (int x = 0; x < mHeight; ++x)
			{
				const char tileType = mapRawData[(mWidth - y - 1) * (mWidth + 1) + x];
				std::shared_ptr<Tile> tile(new Tile(x, y));

				if (tileType == '0')
				{
					tile->SetType(Tile::TILE_SPACE);
				}
				else if (tileType == '1')
				{
					tile->SetType(Tile::TILE_ROAD);
				}

				mTiles.insert(std::make_pair(tile->GetPosition(), tile));
			}
		}
	}
	void Map::Destroy()
	{
		mTiles.clear();
	}

	std::shared_ptr<Tile> Map::GetTile(int x, int y) const
	{
		return GetTile(Position(x, y));
	}
	std::shared_ptr<Tile> Map::GetTile(const Position& pos) const
	{
		auto it = mTiles.find(pos);
		if (it == mTiles.end())
		{
			return nullptr;
		}
		else
		{
			return it->second;
		}
	}

	void Map::ForeachTile(std::function<void(Tile*)> lambda)
	{
		for (auto it : mTiles)
		{
			lambda(it.second.get());
		}
	}
	void Map::ForeachUnit(std::function<void(FieldUnit*)> lambda)
	{
		for (auto it : mUnits)
		{
			lambda(it.second.get());
		}
	}
}