#pragma once
#include "MonoObject.h"
#include"tools.hpp"
class House :public  MonoObject
{
public:
    House();
    void onCrash(MonoObject* collider);
    void onFrameUpdate();
    void onMoveSuccess();
    void onGetMessage(ExMessage message);
private:
    IMAGE picture;
};


