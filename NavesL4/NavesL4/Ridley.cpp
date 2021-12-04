#include "Ridley.h"

Ridley::Ridley(float x, float y, Game* game)
	: Enemy("res/enemigo.png", x, y, 175, 175, game) {

	state = game->stateMoving;

	aDying = new Animation("res/enemigo_morir.png", width, height,
		187, 60, 15, 3, false, game);

	aMoving = new Animation("res/ridley.png", width, height,
		1400, 175, 1, 8, true, game);

	animation = aMoving;

	gravityEffect = false;

	vx = 0;

	vy = 1;
	vyIntelligence = -1;
	vy = vyIntelligence;

	shootTime = 5;
	shootCadence = 50;
	vidas = 25;
}

void Ridley::update() {
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
		if (vy == 0) {
			vyIntelligence = vyIntelligence * -1;
			vy = vyIntelligence;
		}
		if (collisionDown) {
			// mover hacia la izquierda vx tiene que ser negativa
			if (vyIntelligence > 0) {
				vyIntelligence = vyIntelligence * -1;
			}
			vy = vyIntelligence;
		}
		if (collisionUp) {
			// mover hacia la derecha vx tiene que ser positiva
			if (vyIntelligence < 0) {
				vyIntelligence = vyIntelligence * -1;
			}
			vy = vyIntelligence;
		}

	}
	else {
		vy = 0;
	}
}

Projectile* Ridley::shootPlayer(float px, float py) {

	if (shootTime <= 0) {
		shootTime = shootCadence;
		Projectile* projectile = new Projectile("res/disparo_enemigo.png", x, y, game, true);
		projectile->vx = projectile->vx * -1; // Invertir
		return projectile;
	}
	else {
		return NULL;
	}
}

void Ridley::impacted() {
	if (state != game->stateDying) {
		cout << "muerto";
		state = game->stateDying;
		shootTime = 500;
	}
}
