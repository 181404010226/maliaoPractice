
#include "zombie.h"
#include "LevelManager.h"

zombie::zombie()
{
	useGravity = true;
	type = enemy;
	initAnimation(Pangxie_walk);//参数值Man_walk,DebuffMan_walk,Pig_Idle,Pig_Walk,Ghost_fly,Pangxie_walk,Bat_fly,Coin_rotate

}

void zombie::onFrameUpdate()
{
	//GameAudio("PX");

	playAnimation(body.posx, body.posy);
}

void zombie::onCreate()
{
	targerPost1 = body.posx + 100;
	targerPost2 = body.posx - 100;
}

void zombie::onGroud(MonoObject* collider)
{
	// 如果周围有玩家则加速
	vector<MonoObject*> crash = LevelManager::GetInstance().caculateCrash(
		Utils::Rect{ body.posx - 100 ,body.posy - 100,200,200 });
	bool hasPlayer = false;
	for (int i = 0; i < crash.size(); i++)
	{
		if (crash[i]->type == player) hasPlayer = true;
	}
	if (hasPlayer)
	{
		if (vx < 0) vx = -200;
		else vx = 200;
	}
	else
	{
		if (vx < 0) vx = -100;
		else vx = 100;
	}

	if (body.posx >= targerPost1 || body.posx <= targerPost2)
	{
		vx = -vx;
	}
}

void zombie::onCrash(MonoObject* collider)
{
	vx = -vx;
}

zombie::~zombie()
{
}



