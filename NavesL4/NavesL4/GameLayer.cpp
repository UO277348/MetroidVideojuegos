#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	pause = true;
	message = new Actor("res/fondos/mensaje_como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	messageWin = new Actor("res/fondos/mensaje_ganar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	messageLose = new Actor("res/fondos/mensaje_perder.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	gamePad = SDL_GameControllerOpen(0);
	init();
}


void GameLayer::init() {
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, game);
	sala0 = nullptr;
	sala2 = nullptr;
	sala3 = nullptr;
	sala4 = nullptr;
	//game->currentLevel = 3;
	/*buttonJump = new Actor("res/boton_salto.png", WIDTH * 0.9, HEIGHT * 0.55, 100, 100, game);
	buttonShoot = new Actor("res/boton_disparo.png", WIDTH * 0.75, HEIGHT * 0.83, 100, 100, game);*/

	space = new Space(1);
	scrollX = 0;
	scrollY = 0;
	tiles.clear();
	if (game->currentLevel == 3) {
		audioBackground = new Audio("res/sonidos/musica_boss.mp3", true);
	}
	else {
		audioBackground = new Audio("res/sonidos/musica_ambiente.mp3", true);
	}
	audioBackground->play();

	if (player == nullptr)
		vidas = 0;
	else {
		vidas = player->lifes;
	}
	textVidas = new Text("hola", WIDTH * 0.92, HEIGHT * 0.07, game);
	textVidas->content = to_string(vidas);

	if (player == nullptr)
		llaves = 0;
	else {
		llaves = player->llaves;
	}
	textLlaves = new Text("hola", WIDTH * 0.72, HEIGHT * 0.07, game);
	textLlaves->content = to_string(llaves);

	
	background = new Background("res/fondos/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	backgroundPoints = new Actor("res/iconos/icono_puntos.png",
		WIDTH * 0.85, HEIGHT * 0.07, 24, 24, game);
	backgroundLlaves = new Actor("res/iconos/tp_Boss.png",
		WIDTH * 0.65, HEIGHT * 0.07, 24, 40, game);

	buttonPause = new Actor("res/iconos/boton_pausa.png", WIDTH * 0.07, HEIGHT * 0.07, 40, 40, game);

	enemies.clear(); // Vaciar por si reiniciamos el juego
	projectiles.clear(); // Vaciar por si reiniciamos el juego
	recolectables.clear();
	tilesDest.clear();
	
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
	switch (character) {
	case 'E': {
		Enemy* enemy = new Minion(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);

		Tile* tile = new BackgroundTile("res/tiles/background_lvl1.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'R': {
		Enemy* enemy = new Ridley(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);

		Tile* tile = new BackgroundTile("res/tiles/background_lvl1.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'M': {
		Enemy* enemy = new Medusa(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);

		Tile* tile = new BackgroundTile("res/tiles/background_lvl1.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'T': {
		Enemy* enemy = new EnemigoTP(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);

		Tile* tile = new BackgroundTile("res/tiles/background_lvl1.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'V': {
		Recolectable* r = new Recolectable(x, y, game);
		// modificación para empezar a contar desde el suelo.
		r->y = r->y - r->height / 2;
		recolectables.push_back(r);
		space->addDynamicActor(r);

		Tile* tile = new BackgroundTile("res/tiles/background_lvl1.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'S': {
		Recolectable* r = new Arma("res/moneda.png",x, y,40,40, game);
		// modificación para empezar a contar desde el suelo.
		r->y = r->y - r->height / 2;
		recolectables.push_back(r);
		space->addDynamicActor(r);

		Tile* tile = new BackgroundTile("res/tiles/background_lvl1.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '1': {
		if (player == nullptr) {

			player = new Player(x, y, game);
			// modificación para empezar a contar desde el suelo.
			player->y = player->y - player->height / 2;
		}
		else {
			player->x = x;
			player->y = y;
			player->y = player->y - player->height / 2;
		}
		
		space->addDynamicActor(player);

		Tile* tile = new BackgroundTile("res/tiles/background_lvl1.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '0': {
		sala0 = new Tile("res/tp.png", x, y, 40, 66, game);
		// modificación para empezar a contar desde el suelo.
		sala0->y = sala0->y - sala0->height / 2;
		space->addStaticActor(sala0);
		break;
	}
	case '2': {
		sala2 = new Tile("res/tp.png", x, y, 40, 66, game);
		// modificación para empezar a contar desde el suelo.
		sala2->y = sala2->y - sala2->height / 2;
		space->addStaticActor(sala2);
		break;
	}
	case '3': {
		sala3 = new Tile("res/tp.png", x, y, 40, 66, game);
		// modificación para empezar a contar desde el suelo.
		sala3->y = sala3->y - sala3->height / 2;
		space->addStaticActor(sala3);
		break;
	}
	case '4': {
		sala4 = new Tile("res/tp_Boss.png", x, y, 40, 66, game);
		// modificación para empezar a contar desde el suelo.
		sala4->y = sala4->y - sala4->height / 2;
		space->addStaticActor(sala4);
		break;
	}
	case '#': {
		Tile* tile = new Tile("res/tiles/suelo_lvl1.png", x, y,111,63, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'P': {
		Tile* tile = new Tile("res/tiles/pared_lvl1.png", x, y,62,112, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'C': {
		Tile* tile = new BackgroundTile("res/tiles/background_lvl1.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);

		Tile* caja = new TileDestruible("res/tiles/caja_lvl1.png", x, y,80,64, game);
		// modificación para empezar a contar desde el suelo.
		caja->y = caja->y - caja->height / 2;
		tilesDest.push_back(caja);
		space->addStaticActor(caja);
		break;
	}
	case 'Z': {
		Tile* tile = new BackgroundTile("res/tiles/background_lvl1.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);

		Tile* caja = new Tile("res/tiles/plataforma.png", x, y, 45, 10, game);
		// modificación para empezar a contar desde el suelo.
		caja->y = caja->y - caja->height / 2;
		tiles.push_back(caja);
		space->addStaticActor(caja);
		break;
	}
	case '.': {
		Tile* tile = new BackgroundTile("res/tiles/background_lvl1.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
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

		win = false;
		loose = false;
	}
	if (controlShoot) {
		//calculateScroll();
		Projectile* newProjectile = player->shoot(mouseX+scrollX, mouseY+scrollY);
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
	if (sala0 != nullptr) {
		if (sala0->isOverlap(player)) {
			game->currentLevel = 0;
			init();
		}
	}
	if (sala2 != nullptr) {
		if (sala2->isOverlap(player)) {
			game->currentLevel = 1;
			init();
		}
	}

	if (sala3 != nullptr) {
		if (sala3->isOverlap(player)) {
			game->currentLevel = 2;
			init();
		}
	}
	if (sala4 != nullptr) {
		if (sala4->isOverlap(player) && player->llaves == 2) {
			game->currentLevel = 3;
			init();
		}
	}

	space->update();
	background->update();
	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
		Projectile* newProjectile = enemy->shootPlayer(player->x, player->y);
		if (newProjectile != NULL) {
			space->addDynamicActor(newProjectile);
			projectiles.push_back(newProjectile);
		}

		enemy->setPlayerCoords(player->x, player->y);
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
			}
			else{
				player->loseLife();
				if (player->lifes <= 0) {
					loose = true;
					player = nullptr;
					game->currentLevel = 0;
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
	list<Tile*> deleteTiles;
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
			if (enemy->isOverlap(projectile) && !projectile->enemyShot && enemy->vidas <= 1 && !enemy->saltoEncima) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				enemy->impacted();

				if (game->currentLevel == 3) {
					win = true;
					player = nullptr;
					game->currentLevel = 0;
					init();
					return;
				}
			}
			else if (enemy->isOverlap(projectile) && !projectile->enemyShot && enemy->vidas > 1 && !enemy->saltoEncima) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				enemy->vidas-=projectile->daño;
			}

			if (player->isOverlap(projectile) && projectile->enemyShot) {
				player->loseLife();
				if (player->lifes <= 0) {
					loose = true;
					player = nullptr;
					game->currentLevel = 0;
					init();
					return;
				}
			}
		}
	}
	for (auto const& tile : tiles) {
		for (auto const& projectile : projectiles) {
			if (tile->isOverlap(projectile) && tile->isBackgraound==false) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
			}
		}
	}

	for (auto const& tile : tilesDest) {
		for (auto const& projectile : projectiles) {
			if (tile->isOverlap(projectile) && tile->isDestruible == true) {
				bool pInList = std::find(deleteTiles.begin(),
					deleteTiles.end(),
					tile) != deleteTiles.end();

				if (!pInList) {
					deleteTiles.push_back(tile);
				}

				bool pInList2 = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList2) {
					deleteProjectiles.push_back(projectile);
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

				caja->accion(player);
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

	for (auto const& delCaja : deleteTiles) {
		tilesDest.remove(delCaja);
		space->removeStaticActor(delCaja);
	}
	deleteTiles.clear();

	vidas = player->lifes;
	textVidas->content = to_string(vidas);
	llaves = player->llaves;
	textLlaves->content = to_string(llaves);

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

	for (auto const& tile : tilesDest) {
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
	textVidas->draw();

	backgroundLlaves->draw();
	textLlaves->draw();


	buttonPause->draw();

	if (sala0 != nullptr) {
		sala0->draw(scrollX, scrollY);
	}
	if (sala2 != nullptr) {
		sala2->draw(scrollX, scrollY);
	}

	if (sala3 != nullptr) {
		sala3->draw(scrollX, scrollY);
	}
	if (sala4 != nullptr) {
		sala4->draw(scrollX, scrollY);
	}

	// 
	if (pause) {
		message->draw();
	}
	if (win) {
		messageWin->draw();
	}
	if (loose) {
		messageLose->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		SDL_GetMouseState(&mouseX, &mouseY);

		if (buttonPause->containsPoint(mouseX, mouseY)) {
			pause = true;
		}
		else {
			controlShoot = true;
		}
	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		controlShoot = false;
	}
	
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			player->shootMode=1;
			break;
		case SDLK_2:
			if (player->secondaryShoot == true) {
				player->shootMode = 2;
			}
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
			controlContinue = true;
			break;
		case SDLK_p: // dispara
			pause = true;
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
		case SDLK_p: // dispara
			pause = false;
			break;
		}

	}
}

