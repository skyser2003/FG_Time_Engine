#pragma once

#include "Position.h"

namespace CW
{
	class Tile;
	class FieldUnit;

	class Map final
	{
	public:
		Map();
		~Map();

		void Initialize();
		void Destroy();

		void AddUnit(std::shared_ptr<FieldUnit> unit);

		std::shared_ptr<Tile> GetTile(int x, int y) const;
		std::shared_ptr<Tile> GetTile(const Position& pos) const;

		void ForeachTile(std::function<void(Tile*)> lambda);
		void ForeachUnit(std::function<void(FieldUnit*)> lambda);
	private:
		std::map<Position, std::shared_ptr<Tile>> mTiles;
		std::map<Position, std::shared_ptr<FieldUnit>> mUnits;

		int mWidth, mHeight;
	};
}