#pragma once

#include "Actor.h"
#include "Animation.h" 
#include "Player.h" 

class Recolectable : public Actor
{
public:
	Recolectable(float x, float y, Game* game);
	Recolectable(string filename,float x, float y,float fileWidth,float fileHeight, Game* game);

	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();
	virtual void accion(Player* p);

	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada
};

