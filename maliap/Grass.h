#pragma once
#include "MonoObject.h"
#include"tools.hpp"
class Grass :public  MonoObject
{
public:
    Grass();
    void onCrash(MonoObject* collider);
    void onFrameUpdate();
    void onMoveSuccess();
    void onGetMessage(ExMessage message);
private:
    IMAGE picture;

};

