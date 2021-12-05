#include "ProyecilSecundario.h"

ProyecilSecundario::ProyecilSecundario(string filename, float x, float y, float mx, float my, float fileWidth, float fileHeight, Game* game) :
	Projectile(filename,x, y, mx, my, fileWidth,fileHeight, game) {
	daño = 3;
}
