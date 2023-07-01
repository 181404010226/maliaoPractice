#pragma once
#include<iostream>
#include <vector>
#include "LevelManager.h"
#include<algorithm>
#include "MonoObject.h"
#include "AnimationManager.h"

class ghost :public  AnimationManager
{
public:
    ghost();
    void onFrameUpdate();
    void onCreate();
    void onCrash(MonoObject* collider);
    ~ghost();
private:
    //Ñ²Âßµã
    int targerPost1;
    int targerPost2;

};

