#pragma once

#include "Position.h"

namespace CW
{
	class Tile;

	class Map final
	{
	public:
	private:
		std::map<Position, std::shared_ptr<Tile>> mTiles;
	};
}