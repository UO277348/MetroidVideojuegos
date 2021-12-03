#include "TileDestruible.h"

TileDestruible::TileDestruible(string filename, float x, float y, Game* game)
	:Tile(filename, x, y, game) {
	isDestruible = true;
}

TileDestruible::TileDestruible(string filename, float x, float y, int widht, int height, Game* game)
	: Tile(filename, x, y, widht, height, game) {
	isDestruible = true;
}

Recolectable*  TileDestruible::dropItem() {
	Recolectable* vida = new Recolectable(x, y, game);
	return vida;
}
