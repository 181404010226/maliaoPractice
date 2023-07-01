#pragma once
#include "AnimationManager.h"
#include "head.h"

class Bat :public  AnimationManager
{
public:
    Bat();
    ~Bat();
    void onCrash(MonoObject* collider);
    void onFrameUpdate();
    void onMoveSuccess();
    void onCreate();
private:
    //Ѳ�ߵ�
    int targerPost1; 
    int targerPost2;
};