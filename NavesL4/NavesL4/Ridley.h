#pragma once
#include "Actor.h"
#include "Enemy.h"
#include "Animation.h" 
#include "Projectile.h" 

class Ridley : public Enemy
{
public:
	Ridley(float x, float y, Game* game);
	void update() override;
	Projectile* shootPlayer(float px, float py) override;
	void impacted() override;

	float vyIntelligence;
	int parar = 50;
	int pararCadence = 50;
};

