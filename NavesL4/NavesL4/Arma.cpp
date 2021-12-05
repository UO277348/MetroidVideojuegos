#include "Arma.h"

Arma::Arma(string filename, float x, float y, float fileWidth, float fileHeight, Game* game)
	: Recolectable(filename, x, y, fileWidth, fileHeight, game)
{

}

void Arma::accion(Player* p) {
	p->secondaryShoot = true;
	p->llaves++;
}