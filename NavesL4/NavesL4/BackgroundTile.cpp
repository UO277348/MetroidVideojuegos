#include "BackgroundTile.h"

BackgroundTile::BackgroundTile(string filename, float x, float y, Game* game)
	:Tile(filename,x, y, game) {
	isBackgraound = true;
}