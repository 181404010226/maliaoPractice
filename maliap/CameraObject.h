#pragma once
#include "MonoObject.h"
#include "head.h"

// 相机类，用于判断何时清除和生成场景中的物体
class CameraObject :
    public MonoObject
{
public:
    CameraObject();
    void onCreate();
    void onFrameUpdate();
private:
    // 记录上一次更新的位置
    int lastPos;
};

