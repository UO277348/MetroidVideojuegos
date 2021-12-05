#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador/jugador.png", x, y, 64, 77, game) {

	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;
	audioShoot = new Audio("res/sonidos/efecto_disparo.wav", false);


	aShootingRight = new Animation("res/jugador/jugador_disparando_derecha.png",
		width, height, 160, 77, 1, 2, false, game);
	aShootingLeft = new Animation("res/jugador/jugador_disparando_izquierda.png",
		width, height, 160, 77, 1, 2, false, game);

	aShootingUpRight = new Animation("res/jugador/jugador_disparando_arriba_derecha.png",
		width, height, 160, 77, 5, 2, false, game);
	aShootingUpLeft = new Animation("res/jugador/jugador_disparando_arriba_izquierda.png",
		width, height, 160, 77, 5, 2, false, game);

	aShootingDownRight = new Animation("res/jugador/jugador_disparando_abajo_derecha.png",
		width, height, 160, 77, 5, 2, false, game);
	aShootingDownLeft = new Animation("res/jugador/jugador_disparando_abajo_izquierda.png",
		width, height, 160, 77, 5, 2, false, game);


	aJumpingRight = new Animation("res/jugador/jugador_saltando_derecha.png",
		width, height, 350, 77, 15, 5, true, game);
	aJumpingLeft = new Animation("res/jugador/jugador_saltando_izquierda.png",
		width, height, 350, 77, 15, 5, true, game);


	aIdleRight = new Animation("res/jugador/jugador_idle_derecha.png", width, height,
		960, 77, 4, 12, true, game, true, 11);
	aIdleLeft = new Animation("res/jugador/jugador_idle_derecha.png", width, height,
		960, 77, 4, 12, true, game, true, 0);


	aRunningRight = new Animation("res/jugador/jugador_corriendo_derecha.png", width, height,
		1000, 77, 1, 10, true, game);
	aRunningLeft = new Animation("res/jugador/jugador_corriendo_izquierda.png", width, height,
		1000, 77, 1, 10, true, game);


	animation = aIdleRight;

	//gravityEffect = false;
}


void Player::update() {
	//animation->resetFrame();
	// En el aire y movi�ndose, PASA a estar saltando
	if (onAir && state == game->stateMoving) {
		lastState = state;
		state = game->stateJumping;
	}
	// No est� en el aire y estaba saltando, PASA a moverse
	if (!onAir && state == game->stateJumping) {
		lastState = state;
		state = game->stateMoving;
	}


	if (invulnerableTime > 0) {
		invulnerableTime--;
	}

	bool endAnimation = animation->update();

	if (collisionDown == true) {
		onAir = false;
	}
	else {
		onAir = true;
	}


	// Acabo la animaci�n, no sabemos cual
	if (endAnimation) {
		// Estaba disparando
		if (state == game->stateShooting) {
			lastState = state;
			state = game->stateMoving;
		}
	}


	// Establecer orientaci�n
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}


	// Selecci�n de animaci�n basada en estados
	if (state == game->stateJumping) {
		if (orientation == game->orientationRight) {
			animation = aJumpingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aJumpingLeft;
		}
	}
	if (state == game->stateShooting) {
		if (orientation == game->orientationRight) {
			if (pos == 1) {
				animation = aShootingUpLeft;
			}
			if (pos == 2) {
				animation = aShootingDownLeft;
			}
			if (pos == 0) {
				animation = aShootingRight;
			}
			if (pos == 3) {
				animation = aShootingUpRight;
			}
			if (pos == 4) {
				animation = aShootingDownRight;
			}
		}
		if (orientation == game->orientationLeft) {
			if (pos == 1) {
				animation = aShootingUpLeft;
			}
			if (pos == 2) {
				animation = aShootingDownLeft;
			}
			if (pos == 0) {
				animation = aShootingLeft;
			}
			if (pos == 3) {
				animation = aShootingUpRight;
			}
			if (pos == 4) {
				animation = aShootingDownRight;
			}
		}

		pos = 0;
	}
	if (state == game->stateMoving) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				aIdleRight->resetFrame();
				aIdleLeft->resetFrame();
				animation = aRunningRight;
			}
			if (orientation == game->orientationLeft) {
				aIdleRight->resetFrame();
				aIdleLeft->resetFrame();
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

	if (shootTime > 0) {
		shootTime--;
	}

}

void Player::moveX(float axis) {
	vx = axis * 5;
}

void Player::moveY(float axis) {
	vy = axis * 5;
}

Projectile* Player::shoot(int mx, int my) {

	if (shootTime == 0) {
		lastState = state;
		state = game->stateShooting;
		audioShoot->play();
		aShootingLeft->currentFrame = 0; //"Rebobinar" aniamci�n
		aShootingRight->currentFrame = 0; //"Rebobinar" aniamci�n
		shootTime = shootCadence;

		if (mx > x) {
			if (my > y) {
				pos = 4;
			}
			if (my < y) {
				pos = 3;
			}
			if (my == y) {
				pos = 0;
			}

			orientation = game->orientationRight;
		}
		if (mx < x) {
			if (my > y) {
				pos = 2;
			}
			if (my < y) {
				pos = 1;
			}
			if (my == y) {
				pos = 0;
			}
			orientation = game->orientationLeft;
		}

		if (shootMode == 1) {
			Projectile* projectile = new Projectile(x, y, mx, my, game);
			return projectile;
		}
		if (shootMode == 2) {
			Projectile* projectile = new ProyecilSecundario("res/moneda.png",x, y, mx, my,40,40, game);
			return projectile;
		}
	}
	else {
		return NULL;
	}
}

void Player::draw(float scrollX, float scrollY) {
	if (invulnerableTime == 0) {
		animation->draw(x - scrollX, y - scrollY);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			animation->draw(x - scrollX, y - scrollY);
		}
	}
}

void Player::jump() {
	if (!onAir) {
		vy = -17;
		onAir = true;
	}
}

void Player::loseLife() {
	if (invulnerableTime <= 0) {
		if (lifes > 0) {
			lifes--;
			invulnerableTime = 100;
			// 100 actualizaciones 
		}
	}
}

bool Player::saltoEncima(Enemy* enemy) {
	if (y <= enemy->y && enemy->saltoEncima) {

		onAir = false;
		jump();

		return true;
	}
	else
		return false;
}
