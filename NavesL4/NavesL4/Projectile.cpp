#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game) :
	Actor("res/disparo_jugador.png", x, y, 20, 20, game) {
	vx = 9;
	vy = 0; // La gravedad inicial es 1
	this->enemyShot = false;
	gravityEffect = false;
}

Projectile::Projectile(float x, float y, float mx, float my, Game* game) :
	Actor("res/disparo_jugador.png", x, y, 30, 30, game) {
	vx = mx-x;
	vy = my-y; // La gravedad inicial es 1

	vx *= 0.07;
	vy *= 0.07;

	this->enemyShot = false;
	gravityEffect = false;
}

Projectile::Projectile(string filename, float x, float y, Game* game, bool enemyShot) :
	Actor(filename, x, y, 40, 40, game) {
	vx = 9;
	vy = 0; // La gravedad inicial es 1
	this->enemyShot = enemyShot;
	gravityEffect = false;
}

void Projectile::update() {
	vy = vy; // La gravedad suma 1 en cada actualización restamos para anularla 
}
