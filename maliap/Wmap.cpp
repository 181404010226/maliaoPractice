#include "House.h"
#include "Wmap.h"

Wmap::Wmap()
{
	loadimage(&picture, _T("./Image/µØÍ¼.png"), (int)body.width, (int)body.height);
	type = groud;
	canThrough = true;
}

void Wmap::onCrash(MonoObject* collider)
{

}

void Wmap::onFrameUpdate()
{
	static int i = 0;
	drawImg((int)body.posx, (int)body.posy, &picture);
}

void Wmap::onMoveSuccess()
{

}

void Wmap::onGetMessage(ExMessage message)
{

}
