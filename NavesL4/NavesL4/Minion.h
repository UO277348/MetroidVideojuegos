#pragma once

#include "Actor.h"
#include "Enemy.h"
#include "Animation.h" 
#include "Projectile.h" 

class Minion : public Enemy
{
public:
	Minion(float x, float y, Game* game);
	void update();

	int orientation;
	Animation* aMovingRight = nullptr;
	Animation* aDyingRight = nullptr;
};
