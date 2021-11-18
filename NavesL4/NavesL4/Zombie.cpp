#include "Zombie.h"

Zombie::Zombie(float x, float y, Game* game)
	: Enemy("res/enemyidle.png", x, y, 50, 50, game) {

	orientation = game->orientationRight;
	state = game->stateMoving;

	shootTime = 5;
	shootCadence = 50;

	aDyingRight = new Animation("res/enemydieright.png", width, height,
		400, 50, 7, 8, false, game);
	aDyingLeft = new Animation("res/enemydie.png", width, height,
		400, 50, 7, 8, false, game);
	aIdleRight = new Animation("res/enemyidleright.png", width, height,
		150, 50, 3, 3, true, game);
	aIdleLeft = new Animation("res/enemyidle.png", width, height,
		150, 50, 3, 3, true, game);
	aRunningRight = new Animation("res/enemyrunright.png", width, height,
		200, 50, 4, 4, true, game);
	aRunningLeft = new Animation("res/enemyrun.png", width, height,
		200, 50, 4, 4, true, game);

	animation = aIdleRight;

	vx = 3;
	vxIntelligence = -3;
}

void Zombie::update() {

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

	if (state == game->stateMoving) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aRunningRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aRunningLeft;
			}
		}
		if (vx == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeft;
			}
		}
	}
	if (state == game->stateDying) {
		if (orientation == game->orientationRight) {
			animation = aDyingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aDyingLeft;
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

Projectile* Zombie::shootPlayer() {

	if (shootTime <= 0) {
		shootTime = shootCadence;
		Projectile* projectile = new Projectile("res/enemyfireball.png",x, y, game, true);
		if (orientation == game->orientationLeft) {
			projectile->vx = projectile->vx * -1; // Invertir
		}
		return projectile;
	}
	else {
		return NULL;
	}
}

void Zombie::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
		shootTime = 500;
	}
}