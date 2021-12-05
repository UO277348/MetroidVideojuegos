#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Enemy.h"
#include "Minion.h"
#include "Medusa.h"
#include "Ridley.h"
#include "EnemigoTP.h"
#include "Recolectable.h"
#include "Arma.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "BackgroundTile.h"
#include "TileDestruible.h"
#include "Pad.h"

#include "Audio.h"
#include "Space.h" // importar

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	Actor* message;
	Actor* messageWin;
	Actor* messageLose;
	bool pause;
	bool win;
	bool loose;
	// Elementos de interfaz
	SDL_GameController* gamePad;
	Pad* pad;
	Actor* buttonJump;
	Actor* buttonShoot;
	Actor* buttonPause;

	Tile* cup; // Elemento de final de nivel
	Space* space;
	float scrollX;
	int mapWidth;
	float scrollY;
	int mapHeight;
	

	Audio* audioBackground;
	Text* textVidas;
	int vidas;
	Text* textLlaves;
	int llaves;
	int newEnemyTime = 0;
	Player* player;
	Background* background;
	Actor* backgroundPoints;
	Actor* backgroundLlaves;
	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<Recolectable*> recolectables;
	list<Tile*> tiles;
	list<Tile*> tilesDest;

	bool controlContinue = false;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	int mouseX = 0;
	int mouseY = 0;

	Tile* sala0;
	Tile* sala2;
	Tile* sala3;
	Tile* sala4;
};

