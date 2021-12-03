#pragma once
#include "Actor.h"

class Tile : public Actor
{
public:
	Tile(string filename, float x, float y, Game* game);
	Tile(string filename, float x, float y, int widht, int height, Game* game);
	bool isDestruible = false;
};

