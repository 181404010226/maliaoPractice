#pragma once
#include "MonoObject.h"
#include "head.h"

// ����࣬�����жϺ�ʱ��������ɳ����е�����
class CameraObject :
    public MonoObject
{
public:
    CameraObject();
    void onCreate();
    void onFrameUpdate();
private:
    // ��¼��һ�θ��µ�λ��
    int lastPos;
};

