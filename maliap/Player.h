#pragma once
#include "AnimationManager.h"
#include"head.h"

//����ӵ�
#include "LevelManager.h"


class Player :public  AnimationManager
{
public:
    IMAGE image_play;
    Player();
    void onGetMessage(ExMessage message);

    void onCrash(MonoObject* collider);
    void onFrameUpdate();
    //void onMoveSuccess();
    void onGroud(MonoObject* collider);
private:
    AnimationManager* palyerAnim;
    void jump();
    void nopush();
    // �ж��Ƿ�ֹ�����ڲ��Ŷ�����
    bool stand = true;
    bool KEYA = false;
    bool KEYD = false;
    // �ж��Ƿ��ܵ��˺�
    bool heated = false;
    // �ж��Ƿ��ܹ���Ծ
    bool canJump = true;
    int push_x = 0;
    int push_y = 0;
    IMAGE love;
    //bool isMove = false;
};
