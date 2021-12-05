#include "Medusa.h"

Medusa::Medusa(float x, float y, Game* game)
	: Enemy("res/enemyidle.png", x, y, 40, 40, game) {

	state = game->stateMoving;

	aDying = new Animation("res/enemigo_voladorDead.png", width, height,
		746, 41, 8, 14, false, game);

	aMoving = new Animation("res/enemigo_volador.png", width, height,
		746, 41, 8, 14, true, game);

	animation = aMoving;

	gravityEffect = false;

	vx = 0;

	vx = 1;
	vxIntelligence = -1;
	vx = vxIntelligence;

	shootTime = 5;
	shootCadence = 50;
	vidas = 1;
}

void Medusa::update() {

	if (shootTime > 0) {
		shootTime--;
	}

	bool endAnimation = animation->update();

	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
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
}

Projectile* Medusa::shootPlayer(float px, float py) {

	if (shootTime <= 0) {
		shootTime = shootCadence;
		Projectile* projectile = new Projectile("res/enemyfireball.png",x, y,px,py,30,30, game, true);
		return projectile;
	}
	else {
		return NULL;
	}
}

void Medusa::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
		shootTime = 500;
	}
}