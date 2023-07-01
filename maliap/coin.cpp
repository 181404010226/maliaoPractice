#include "coin.h"


coin::coin()
{
	initAnimation(Coin_rotate);
}
void coin::onCrash(MonoObject* collider)
{//≈–∂œ
	if (collider->type == player)
	{
		GameAudio(11);
		collider->score += 10;
		DestroyObject(this);
	}
}

void coin::onFrameUpdate()
{//ªÊ÷∆µ¿æﬂ
	playAnimation(body.posx, body.posy);
}

void coin::onMoveSuccess()
{
}

void coin::onGetMessage(ExMessage message)
{
}