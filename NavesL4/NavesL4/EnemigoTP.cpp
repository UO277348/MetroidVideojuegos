#include "EnemigoTP.h"

EnemigoTP::EnemigoTP(float x, float y, Game* game)
	: Enemy("res/enemigo.png", x, y, 120, 98, game) {

	state = game->stateMoving;
	orientation = game->orientationRight;

	aDying = new Animation("res/enemigo_tpDead.png", width, height,
		120, 98, 1, 1, false, game);
	aDyingRight = new Animation("res/enemigo_tp_rightDead.png", width, height,
		120, 98, 1, 1, false, game);

	aMoving = new Animation("res/enemigo_tp.png", width, height,
		120, 98, 1, 1, true, game);
	aMovingRight = new Animation("res/enemigo_tp_right.png", width, height,
		120, 98, 1, 1, true, game);

	animation = aMoving;

	vx = 0;
	vxIntelligence = 0;
	vx = vxIntelligence;

	vidas = 6;

	tpTime = 10;
	tpCadence = 50;

	shootTime = 10;
	shootCadence = 25;
}

void EnemigoTP::update() {
	bool endAnimation = animation->update();

	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
	}
	if (tpTime <= 0) {
		tpTime = tpCadence;
		calcularCoords();
	}
	else 
		tpTime--;

	if (shootTime <= 0) {
		shootTime = shootCadence;
	}
	else
		shootTime--;

	if (x < playerX) {
		orientation = game->orientationRight;
	}
	if (x > playerX) {
		orientation = game->orientationLeft;
	}

	if (state == game->stateMoving) {
		if (orientation == game->orientationRight) {
			animation = aMovingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aMoving;
		}
	}
	if (state == game->stateDying) {
		if (orientation == game->orientationRight) {
			animation = aDyingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aDying;
		}
	}
}

void EnemigoTP::calcularCoords() {

	int random = rand() % 100;

	if(random<50)
		x = playerX + 200;
	else
		x = playerX - 200;
	y = playerY-10;
}

Projectile* EnemigoTP::shootPlayer(float px, float py) {

	if (shootTime <= 0) {
		shootTime = shootCadence;
		Projectile* projectile = new Projectile("res/disparo_enemigo.png", x, y, px, py, 40, 40, game, true);
		return projectile;
	}
	else {
		return NULL;
	}
}

void EnemigoTP::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
		shootTime = 500;
	}
}
