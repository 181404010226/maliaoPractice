#pragma once
#include "MonoObject.h"
class testWall :public  MonoObject
{
public:
    testWall();
    void onCrash(MonoObject* collider);
    void onFrameUpdate();
    void onMoveSuccess();
    void onGroud(MonoObject* collider);
private:

    int score = 5;
};

