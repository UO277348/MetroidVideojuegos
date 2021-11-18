#pragma once

#include "Enemy.h"

class Cuervo : public Enemy
{
public:
	Cuervo(float x, float y, Game* game);

	void update() override;

	float vyIntelligence;
};

