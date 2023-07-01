#include "Grass.h"

Grass::Grass()
{
	loadimage(&picture, _T("./Image/grass(60x36).png"), (int)body.width, (int)body.height);
	type = groud;
	canThrough = true;
}

void Grass::onCrash(MonoObject* collider)
{

}

void Grass::onFrameUpdate()
{
	static int i = 0;
	drawImg((int)body.posx, (int)body.posy,&picture);
}

void Grass::onMoveSuccess()
{

}

void Grass::onGetMessage(ExMessage message)
{

}
