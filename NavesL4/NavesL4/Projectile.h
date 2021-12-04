#pragma once

#include "Actor.h"


class Projectile : public Actor
{
public:
	Projectile(float x, float y, Game* game);
	Projectile(float x, float y, float mx, float my, Game* game);
	Projectile(string filename, float x, float y, Game* game, bool enemyShot);
	Projectile(string filename, float x, float y, float fileWidth, float fileHeight, Game* game, bool enemyShot);
	Projectile(string filename, float x, float y, float px, float py, float fileWidth, float fileHeight, Game* game, bool enemyShot);

	bool enemyShot;
	void update();
};

