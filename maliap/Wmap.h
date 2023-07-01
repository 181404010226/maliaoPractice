#pragma once
#include "MonoObject.h"
#include"tools.hpp"
class Wmap :public  MonoObject
{
public:
    Wmap();
    void onCrash(MonoObject* collider);
    void onFrameUpdate();
    void onMoveSuccess();
    void onGetMessage(ExMessage message);
private:
    IMAGE picture;
};


