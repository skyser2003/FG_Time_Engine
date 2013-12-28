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
		std::shared_ptr<Tile> GetTile() const { return mTile; }

		int GetX() const;
		int GetY() const;
	private:
		std::shared_ptr<Tile> mTile;
	};
}