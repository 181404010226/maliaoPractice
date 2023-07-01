#include "Cloud.h"

Cloud::Cloud()
{
	loadimage(&picture, _T("./Image/ÔÆ.png"), (int)body.width, (int)body.height);
	type = groud;
	canThrough = true;
}

void Cloud::onCrash(MonoObject* collider)
{

}

void Cloud::onFrameUpdate()
{
	static int i = 0;
	drawImg((int)body.posx, (int)body.posy, &picture);
}

void Cloud::onMoveSuccess()
{

}

void Cloud::onGetMessage(ExMessage message)
{

}
