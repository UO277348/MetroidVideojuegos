#pragma once

#include "Enemy.h"

class Medusa : public Enemy
{
public:
	Medusa(float x, float y, Game* game);

	void update() override;
	Projectile* shootPlayer(float px, float py) override;
	void impacted() override;

};

