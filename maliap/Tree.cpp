#include "Tree.h"

Tree::Tree()
{
	loadimage(&picture, _T("./Image/ÂÌÊ÷(60x69).png"), (int)body.width, (int)body.height);
	//loadimage(&picture, _T("./Image/ÂÌÊ÷(60x69).png"), (int)body.width, (int)body.height);
	type = groud;
	canThrough = true;
}

void Tree::onCrash(MonoObject* collider)
{

}

void Tree::onFrameUpdate()
{
	static int i = 0;
	drawImg((int)body.posx, (int)body.posy, &picture);
}

void Tree::onMoveSuccess()
{

}

void Tree::onGetMessage(ExMessage message)
{

}
