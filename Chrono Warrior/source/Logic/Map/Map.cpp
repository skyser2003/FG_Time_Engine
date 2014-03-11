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

				mTiles.push_back(tile);
			}
		}
	}
	void Map::Destroy()
	{
		mTiles.clear();
	}

	void Map::AddUnit(std::shared_ptr<FieldUnit> unit)
	{
		mUnits.push_back(unit);
	}
	std::vector<std::shared_ptr<FieldUnit>> Map::GetUnits(int x, int y) const
	{
		return GetUnits(Position(x, y));
	}
	std::vector<std::shared_ptr<FieldUnit>> Map::GetUnits(const Position& pos) const
	{
		std::vector<std::shared_ptr<FieldUnit>> units;

		for (auto it : mUnits)
		{
			const Position& unitPos = it->GetPosition();
			if (unitPos == pos)
			{
				units.push_back(it);
			}
		}

		return units;
	}

	std::shared_ptr<Tile> Map::GetTile(int x, int y) const
	{
		return GetTile(Position(x, y));
	}
	std::shared_ptr<Tile> Map::GetTile(const Position& pos) const
	{
		for (auto tile : mTiles)
		{
			if (tile->GetPosition() == pos)
			{
				return tile;
			}
		}

		return nullptr;
	}

	void Map::ForeachTile(std::function<void(Tile*)> lambda)
	{
		for (auto tile : mTiles)
		{
			lambda(tile.get());
		}
	}
	void Map::ForeachUnit(std::function<void(FieldUnit*)> lambda)
	{
		for (auto unit : mUnits)
		{
			lambda(unit.get());
		}
	}
}