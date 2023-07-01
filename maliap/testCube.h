#pragma once
#include "MonoObject.h"
#include "head.h"
#include"tools.hpp"
class testCube :public  MonoObject
{
public:
    testCube();
    void onCrash(MonoObject* collider);
    void onFrameUpdate();
    void onMoveSuccess();
    void onGetMessage(ExMessage message);
private:
    IMAGE picture;
    int life = 5;
    int x=100, y=100;
};

