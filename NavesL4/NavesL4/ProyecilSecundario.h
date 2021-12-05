#pragma once
#include "Projectile.h"

class ProyecilSecundario : public Projectile
{
public:
	ProyecilSecundario(string filename, float x, float y, float mx, float my, float fileWidth, float fileHeight, Game* game);
};

