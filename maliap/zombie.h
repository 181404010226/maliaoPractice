#pragma once
#include "MonoObject.h"
#include "AnimationManager.h"
class zombie :public  AnimationManager
{
public:
    zombie();
    void onFrameUpdate();
    void onCreate();
    void onGroud(MonoObject* collider);
    void onCrash(MonoObject* collider);
    ~zombie();
private:
    //Ñ²Âßµã
    int targerPost1;
    int targerPost2;

};

