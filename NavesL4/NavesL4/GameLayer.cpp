#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	pause = true;
	message = new Actor("res/fondos/mensaje_como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	gamePad = SDL_GameControllerOpen(0);
	init();
}


void GameLayer::init() {
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, game);

	/*buttonJump = new Actor("res/boton_salto.png", WIDTH * 0.9, HEIGHT * 0.55, 100, 100, game);
	buttonShoot = new Actor("res/boton_disparo.png", WIDTH * 0.75, HEIGHT * 0.83, 100, 100, game);*/

	space = new Space(1);
	scrollX = 0;
	scrollY = 0;
	tiles.clear();

	audioBackground = new Audio("res/sonidos/musica_ambiente.mp3", true);
	audioBackground->play();

	points = 0;
	textPoints = new Text("hola", WIDTH * 0.92, HEIGHT * 0.07, game);
	textPoints->content = to_string(points);

	pointsRecolestables = 0;
	textRecolectables = new Text("hola", WIDTH * 0.72, HEIGHT * 0.07, game);
	textRecolectables->content = to_string(pointsRecolestables);

	
	background = new Background("res/fondos/fondo_2.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	backgroundPoints = new Actor("res/iconos/icono_puntos.png",
		WIDTH * 0.85, HEIGHT * 0.07, 24, 24, game);
	backgroundRecolectables = new Actor("res/iconos/icono_recolectable.png",
		WIDTH * 0.65, HEIGHT * 0.07, 40, 40, game);

	enemies.clear(); // Vaciar por si reiniciamos el juego
	projectiles.clear(); // Vaciar por si reiniciamos el juego
	recolectables.clear();

	loadMap("res/" + to_string(game->currentLevel) + ".txt");
}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			mapHeight = line.length() * 32; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	Tile* tile = new BackgroundTile("res/tiles/background_lvl1.png", x, y, game);
	tile->y = tile->y - tile->height / 2;
	tiles.push_back(tile);
	space->addStaticActor(tile);

	switch (character) {
	case 'E': {
		Enemy* enemy = new Minion(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'Z': {
		Enemy* enemy = new Zombie(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'V': {
		Recolectable* r = new Recolectable(x, y, game);
		// modificación para empezar a contar desde el suelo.
		r->y = r->y - r->height / 2;
		recolectables.push_back(r);
		space->addDynamicActor(r);
		break;
	}
	case '1': {
		player = new Player(x, y, game);
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		break;
	}
	case '#': {
		Tile* tile = new Tile("res/tiles/suelo_lvl1.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '(': {
		Tile* tile = new BackgroundTile("res/tiles/vaya_lvl1.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case ')': {
		Tile* tile = new BackgroundTile("res/tiles/vaya2_lvl1.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	}
}


void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		// Cambio automático de input
		// PONER el GamePad
		game->input = game->inputKeyboard;

		// Procesar teclas
		keysToControls(event);

	}
	//procesar controles
	//procesar controles
	// Disparar
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			space->addDynamicActor(newProjectile);
			projectiles.push_back(newProjectile);
		}

	}

	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
	
	}
	else if (controlMoveY < 0) {
		player->jump();
	}
	else {

	}



}

void GameLayer::update() {
	if (pause) {
		return;
	}

	// Nivel superado
	/*if (cup->isOverlap(player)) {
		game->currentLevel++;
		if (game->currentLevel > game->finalLevel) {
			game->currentLevel = 0;
		}
		message = new Actor("res/mensaje_ganar.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
		pause = true;
		init();
	}*/

	// Jugador se cae
	if (player->y > HEIGHT + 80) {
		init();
	}

	space->update();
	background->update();
	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
		Projectile* newProjectile = enemy->shootPlayer();
		if (newProjectile != NULL) {
			space->addDynamicActor(newProjectile);
			projectiles.push_back(newProjectile);
		}
	}
	for (auto const& projectile : projectiles) {
		projectile->update();
	}
	for (auto const& r : recolectables) {
		r->update();
	}


	// Colisiones
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy) && enemy->state != game->stateDying && enemy->state != game->stateDead) {
			if (player->saltoEncima(enemy)) {
				enemy->impacted();
				points++;
				textPoints->content = to_string(points);
			}
			else{
				player->loseLife();
				if (player->lifes <= 0) {
					init();
					return;
				}
			}
		}
	}

	// Colisiones , Enemy - Projectile

	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	list<Recolectable*> deleteRecos;
	for (auto const& projectile : projectiles) {
		if (projectile->isInRender(scrollX, scrollY) == false || projectile->vx == 0) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}



	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile) && !projectile->enemyShot && enemy->vidas == 1 && !enemy->saltoEncima) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}


				enemy->impacted();
				points++;
				textPoints->content = to_string(points);


			}
			else if (enemy->isOverlap(projectile) && !projectile->enemyShot && enemy->vidas > 1 && !enemy->saltoEncima) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				enemy->vidas--;
			}

			if (player->isOverlap(projectile) && projectile->enemyShot) {
				player->loseLife();
				if (player->lifes <= 0) {
					init();
					return;
				}
			}
		}
	}

	for (auto const& caja : recolectables) {
		if (player->isOverlap(caja)) {
			bool cajaInList = std::find(deleteRecos.begin(),
				deleteRecos.end(),
				caja) != deleteRecos.end();

			if (!cajaInList) {
				deleteRecos.push_back(caja);

				player->lifes++;
				pointsRecolestables++;
				textRecolectables->content = to_string(pointsRecolestables);
			}
		}
	}

	for (auto const& enemy : enemies) {
		if (enemy->state == game->stateDead) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
		}
	}

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();

	for (auto const& delCaja : deleteRecos) {
		recolectables.remove(delCaja);
		space->removeDynamicActor(delCaja);
	}
	deleteRecos.clear();

	cout << "update GameLayer" << endl;
}

void GameLayer::calculateScroll() {
	// limite izquierda
	if (player->x > WIDTH * 0.3) {
		if (player->x - scrollX < WIDTH * 0.3) {
			scrollX = player->x - WIDTH * 0.3;
		}
	}

	// limite derecha
	if (player->x < mapWidth - WIDTH * 0.3) {
		if (player->x - scrollX > WIDTH * 0.7) {
			scrollX = player->x - WIDTH * 0.7;
		}
	}

	// limite izquierda
	if (player->y > HEIGHT * 0.3) {
		if (player->y - scrollY < HEIGHT * 0.3) {
			scrollY = player->y - HEIGHT * 0.3;
		}
	}

	// limite derecha
	if (player->y < mapHeight - HEIGHT * 0.3) {
		if (player->y - scrollY > HEIGHT * 0.7) {
			scrollY = player->y - HEIGHT * 0.7;
		}
	}
}

void GameLayer::draw() {
	calculateScroll();

	background->draw();
	for (auto const& tile : tiles) {
		tile->draw(scrollX, scrollY);
	}

	for (auto const& projectile : projectiles) {
		projectile->draw(scrollX, scrollY);
	}
	/*cup->draw(scrollX, scrollY);*/
	player->draw(scrollX, scrollY);
	for (auto const& enemy : enemies) {
		enemy->draw(scrollX, scrollY);
	}

	for (auto const& r : recolectables) {
		r->draw(scrollX, scrollY);
	}

	backgroundPoints->draw();
	textPoints->draw();

	backgroundRecolectables->draw();
	textRecolectables->draw();

	// 
	if (pause) {
		message->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
	}

	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}
	}
}

