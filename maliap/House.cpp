#include "House.h"
#include <vector>
#include "LevelManager.h"

House::House()
{
	loadimage(&picture, _T("./Image/三角屋(60x73).png"), (int)body.width, (int)body.height);
	type = groud;
	canThrough = true;
}

void House::onCrash(MonoObject* collider)
{

}

void House::onFrameUpdate()
{
	static int i = 0;
	drawImg((int)body.posx, (int)body.posy, &picture);
	// 如果胜利
	vector<MonoObject*> crash = LevelManager::GetInstance().caculateCrash(
		Utils::Rect{ body.posx ,body.posy ,60,60 });
	for (int i = 0; i < crash.size(); i++)
	{
		if (crash[i]->type == player) Sceneconfig::GetInstance()->flag = 3;
	}
	
}

void House::onMoveSuccess()
{

}

void House::onGetMessage(ExMessage message)
{

}
