#include "Minion.h"

Minion::Minion(float x, float y, Game* game)
	: Enemy("res/enemigo.png", x, y, 40, 90, game) {

	state = game->stateMoving;
	orientation = game->orientationRight;

	aDying = new Animation("res/enemigo_morir.png", width, height,
		187, 60, 15, 3, false, game);
	aDyingRight = new Animation("res/enemigo_morir.png", width, height,
		187, 60, 15, 3, false, game);

	aMoving = new Animation("res/enemigo_movimiento.png", width, height,
		1090, 95, 6, 13, true, game);
	aMovingRight = new Animation("res/enemigo_movimiento_right.png", width, height,
		1013, 95, 6, 13, true, game);

	animation = aMoving;

	vx = 1;
	vxIntelligence = -1;
	vx = vxIntelligence;

	vidas = 3;
}

void Minion::update() {
	bool endAnimation = animation->update();

	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
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

	// Establecer velocidad
	if (state != game->stateDying) {
		// no está muerto y se ha quedado parado
		if (vx == 0) {
			vxIntelligence = vxIntelligence * -1;
			vx = vxIntelligence;
		}
		if (outRight) {
			// mover hacia la izquierda vx tiene que ser negativa
			if (vxIntelligence > 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}
		if (outLeft) {
			// mover hacia la derecha vx tiene que ser positiva
			if (vxIntelligence < 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}

	}
	else {
		vx = 0;
	}

	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}
}
