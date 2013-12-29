#pragma once

#include "Position.h"

namespace CW
{
	class Tile;

	class Map final
	{
	public:
		Map();
		~Map();

		void Initialize();
		void Destroy();

		std::shared_ptr<Tile> GetTile(int x, int y) const;
		std::shared_ptr<Tile> GetTile(const Position& pos) const;

		void ForeachTile(std::function<void(Tile*)> lambda);
	private:
		std::map<Position, std::shared_ptr<Tile>> mTiles;
	};
}