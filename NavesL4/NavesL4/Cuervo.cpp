#include "Cuervo.h"

Cuervo::Cuervo(float x, float y, Game* game)
	: Enemy("res/cuervo_1.png", x, y, 40, 40, game) {

	aDying = new Animation("res/pajaro_dead.png", width, height,
		600, 60, 10, 10, false, game);

	aMoving = new Animation("res/animacion_cuervo.png", width, height,
		320, 40, 8, 8, true, game);
	animation = aMoving;

	vx = 1;
	vxIntelligence = -1;

	vy = 1;
	vyIntelligence = 1;

	gravityEffect = false;

	volarTime = 15;
	volarCadence = 15;
}


void Cuervo::update() {

	volarTime--;

	bool endAnimation = animation->update();

	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
	}

	if (state == game->stateMoving) {
		animation = aMoving;
	}
	if (state == game->stateDying) {
		animation = aDying;
	}

	// Establecer velocidad
	if (state != game->stateDying) {
		// no está muerto y se ha quedado parado
		if (vx == 0) {
			vxIntelligence = vxIntelligence * -1;
			vx = vxIntelligence;
		}

		if (vy == 0) {
			vyIntelligence = vyIntelligence * -1;
			vy = vyIntelligence;
		}

		if (collisionDown) {
			if (vyIntelligence > 0) {
				vyIntelligence = vyIntelligence * -1;
			}
			vy = vyIntelligence;

			volarTime = volarCadence;
		}

		if (collisionUp) {
			if (vyIntelligence < 0) {
				vyIntelligence = vyIntelligence * -1;
			}
			vy = vyIntelligence;

			volarTime = volarCadence;
		}

		if (volarTime <= 0) {
			vyIntelligence = vyIntelligence * -1;
			vy = vyIntelligence;
			volarTime = volarCadence;
		}
	}
	else {
		vx = 0;
		vy = 0;
	}
}