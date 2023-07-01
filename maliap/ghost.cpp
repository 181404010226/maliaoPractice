#include"ghost.h"

ghost::ghost()
{
    type = enemy;
    initAnimation(Ghost_fly);//����ֵMan_walk,DebuffMan_walk,Pig_Idle,Pig_Walk,Ghost_fly,Pangxie_walk,Bat_fly,Coin_rotate
    vx = 100;
}
ghost::~ghost()
{

    cout << "�ڴ����ͷ�" << endl;
}
void ghost::onCreate()
{
    targerPost1 = body.posx + 100;
    targerPost2 = body.posx - 100;
}

void ghost::onCrash(MonoObject* collider)
{
    vx = -vx;
}

void ghost::onFrameUpdate()
{

    if (body.posx >= targerPost1 || body.posx <= targerPost2)
    {
        vx = -vx;
    }
    playAnimation(body.posx, body.posy);
    //  GameAudio("BF");
}
