#include "coin.h"


coin::coin()
{
	initAnimation(Coin_rotate);
}
void coin::onCrash(MonoObject* collider)
{//�ж�
	if (collider->type == player)
	{
		GameAudio(11);
		collider->score += 10;
		DestroyObject(this);
	}
}

void coin::onFrameUpdate()
{//���Ƶ���
	playAnimation(body.posx, body.posy);
}

void coin::onMoveSuccess()
{
}

void coin::onGetMessage(ExMessage message)
{
}