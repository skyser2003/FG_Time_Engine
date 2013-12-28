#include "stdafx.h"
#include "Map.h"

#include "Tile.h"

namespace CW
{
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