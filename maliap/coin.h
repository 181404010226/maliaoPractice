#pragma once
#include "AnimationManager.h"
#include "LevelManager.h"
class coin :
    public AnimationManager
{
public:
    coin();
    void onCrash(MonoObject* collider);
    void onFrameUpdate();
    void onMoveSuccess();
    void onGetMessage(ExMessage message);
};

