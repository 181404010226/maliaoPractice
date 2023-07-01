#pragma once
#include "MonoObject.h"
#include"tools.hpp"
class Cloud :public  MonoObject
{
public:
    Cloud();
    void onCrash(MonoObject* collider);
    void onFrameUpdate();
    void onMoveSuccess();
    void onGetMessage(ExMessage message);
private:
    IMAGE picture;

};

