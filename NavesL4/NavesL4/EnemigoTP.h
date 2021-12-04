#pragma once
#include "Actor.h"
#include "Enemy.h"
#include "Animation.h" 
#include "Projectile.h" 

class EnemigoTP : public Enemy
{
public:
	EnemigoTP(float x, float y, Game* game);
	void update() override;
	void calcularCoords();

	int orientation;
	Animation* aMovingRight = nullptr;
	Animation* aDyingRight = nullptr;
};

