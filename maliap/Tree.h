#pragma once
#include "MonoObject.h"
#include"tools.hpp"
class Tree :public  MonoObject
{
public:
    Tree();
    void onCrash(MonoObject* collider);
    void onFrameUpdate();
    void onMoveSuccess();
    void onGetMessage(ExMessage message);
private:
    IMAGE picture;
    //int life = 5;
    //int x = 100, y = 100;
};

