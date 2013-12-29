#include "stdafx.h"
#include "Map.h"

#include "Tile.h"

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
		mTiles.insert(std::make_pair(Position(1, 0), std::shared_ptr<Tile>(new Tile)));
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
}