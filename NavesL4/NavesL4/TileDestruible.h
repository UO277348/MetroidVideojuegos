#pragma once
#include "Tile.h"
#include "Recolectable.h"
class TileDestruible : public Tile
{
	public: 
		TileDestruible(string filename, float x, float y, Game* game);
		TileDestruible(string filename, float x, float y, int widht, int height, Game* game);

		Recolectable* dropItem();
};

