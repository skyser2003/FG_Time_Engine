#pragma once

namespace CW
{
	class Tile;

	class FieldObject
	{
	public:
		virtual ~FieldObject();

		virtual void Initialize();
		virtual void Destroy();

		void SetTile(const std::shared_ptr<Tile>& tile);

		int GetX() const;
		int GetY() const;
	private:
		std::shared_ptr<Tile> mTile;
	};
}