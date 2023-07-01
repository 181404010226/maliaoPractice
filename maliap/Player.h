#pragma once
#include "AnimationManager.h"
#include"head.h"

//后面加的
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
    // 判断是否静止，用于播放动画。
    bool stand = true;
    bool KEYA = false;
    bool KEYD = false;
    // 判断是否受到伤害
    bool heated = false;
    // 判断是否能够跳跃
    bool canJump = true;
    int push_x = 0;
    int push_y = 0;
    IMAGE love;
    //bool isMove = false;
};
