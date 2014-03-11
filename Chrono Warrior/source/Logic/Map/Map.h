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
		std::vector<std::shared_ptr<FieldUnit>> GetUnits(int x, int y) const;
		std::vector<std::shared_ptr<FieldUnit>> GetUnits(const Position& pos) const;

		std::shared_ptr<Tile> GetTile(int x, int y) const;
		std::shared_ptr<Tile> GetTile(const Position& pos) const;

		void ForeachTile(std::function<void(Tile*)> lambda);
		void ForeachUnit(std::function<void(FieldUnit*)> lambda);
	private:
		std::vector<std::shared_ptr<Tile>> mTiles;
		std::vector<std::shared_ptr<FieldUnit>> mUnits;

		int mWidth, mHeight;
	};
}