#include "EnemigoTP.h"

EnemigoTP::EnemigoTP(float x, float y, Game* game)
	: Enemy("res/enemigo.png", x, y, 120, 98, game) {

	state = game->stateMoving;
	orientation = game->orientationRight;

	aDying = new Animation("res/enemigo_morir.png", width, height,
		187, 60, 15, 1, false, game);
	aDyingRight = new Animation("res/enemigo_morir.png", width, height,
		187, 60, 15, 1, false, game);

	aMoving = new Animation("res/enemigo_tp.png", width, height,
		120, 98, 1, 1, true, game);
	aMovingRight = new Animation("res/enemigo_tp_right.png", width, height,
		120, 98, 1, 1, true, game);

	animation = aMoving;

	vx = 0;
	vxIntelligence = 0;
	vx = vxIntelligence;

	vidas = 6;
}

void EnemigoTP::update() {
	bool endAnimation = animation->update();

	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
	}

	calcularCoords();

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
	x = playerX + 100;
	y = playerY-10;
}
