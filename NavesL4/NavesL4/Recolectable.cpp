#include "Recolectable.h"

Recolectable::Recolectable(float x, float y, Game* game)
	: Actor("res/icono_recolectable.png", x, y, 40, 40, game)
{
	vx = 0;
	aMoving = new Animation("res/recolectable.png", width, height,
		256, 32, 8, 8, true, game);
	animation = aMoving;
}

Recolectable::Recolectable(string filename, float x, float y, float fileWidth, float fileHeight, Game* game)
	: Actor(filename, x, y, fileWidth, fileHeight, game)
{
	vx = 0;
	aMoving = new Animation(filename, width, height,
		256, 32, 1, 1, true, game);
	animation = aMoving;
}

void Recolectable::update() {
	animation->update();
}

void Recolectable::draw(float scrollX, float scrollY) {
	//Actor::draw(); // llamar al metodo del hijo

	animation->draw(x - scrollX, y - scrollY);

}

void Recolectable::accion(Player* p) {
	p->lifes++;
	p->llaves++;
}
