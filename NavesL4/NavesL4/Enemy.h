#pragma once

#include "Actor.h"
#include "Animation.h" 
#include "Projectile.h"

class Enemy : public Actor
{
public:
	Enemy(string filename, float x, float y, float fileWidth, float fileHeight, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	virtual void update();
	virtual void impacted(); // Recibe impacto y pone animación de morir
	void setPlayerCoords(int px, int py);

	Animation* aDying = aDying;
	Animation* aMoving = nullptr;
	Animation* animation = nullptr; // Referencia a la animación mostrada

	float vxIntelligence;
	int state;

	int vidas = 1;
	int shootCadence = 0;
	int shootTime = -1;
	int volarCadence = 0;
	int volarTime = -1;
	virtual Projectile* shootPlayer(float px, float py);

	int playerX;
	int playerY;

	bool saltoEncima = false;
};

