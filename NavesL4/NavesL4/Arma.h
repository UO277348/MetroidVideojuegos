#pragma once

#include "Recolectable.h"

class Arma : public Recolectable
{
public:
	Arma(string filename, float x, float y, float fileWidth, float fileHeight, Game* game);

	void accion(Player* p) override;
};

