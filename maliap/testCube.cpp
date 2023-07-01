#include "testCube.h"

testCube::testCube()
{
	loadimage(&picture, _T("./Image/groud.png"), (int)body.width, (int)body.height);
	type = groud;
}

void testCube::onCrash(MonoObject* collider)
{
	
}

void testCube::onFrameUpdate()
{
	drawImg((int)body.posx, (int)body.posy,&picture);
	// fillrectangle((int)body.posy, (int)body.posy + (int)body.height, (int)body.posx + (int)body.width, );
}

void testCube::onMoveSuccess()
{
}

void testCube::onGetMessage(ExMessage message)
{
}
