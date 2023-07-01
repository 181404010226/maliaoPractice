#include"Bat.h"

Bat::Bat()
{
    type = enemy;
    initAnimation(Bat_fly);//参数值Man_walk,DebuffMan_walk,Pig_Idle,Pig_Walk,Ghost_fly,Pangxie_walk,Bat_fly,Coin_rotate
    vy = 100;
}
Bat::~Bat()
{

    cout << "内存已释放" << endl;
}
void Bat::onCreate()
{
    targerPost1 = body.posy + 55;
    targerPost2 = body.posy - 55;
}
void Bat::onCrash(MonoObject* collider)
{
    vy = -vy;
}

void Bat::onFrameUpdate() {

    if (body.posy >= targerPost1 || body.posy <= targerPost2)
    {
        vy = -vy;
    }
    playAnimation(body.posx, body.posy);
}

void Bat::onMoveSuccess()
{
}
