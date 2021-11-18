#pragma once

#include "Enemy.h"

class Zombie : public Enemy
{
public:
	Zombie(float x, float y, Game* game);

	void update() override;
	Projectile* shootPlayer() override;
	void impacted() override;
	int orientation;

	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aDyingRight;
	Animation* aDyingLeft;
	Animation* aRunningRight;
	Animation* aRunningLeft;
};

