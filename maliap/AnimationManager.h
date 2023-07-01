#pragma once
#include "MonoObject.h"
#include<map>
#include<vector>
#include<easyx.h>
#include "tools.hpp"
using namespace std;

//��������
enum animationType
{
    Man_Idle,
    Man_walk,
    DebuffMan_walk,
    Pig_Idle,
    Pig_Walk,
    Ghost_fly,
    Pangxie_walk,
    Bat_fly,
    Coin_rotate
};
class AnimationManager :public  MonoObject
{
public:
    AnimationManager(); 
    virtual ~AnimationManager();
    void onCrash(MonoObject collider);
    void onFrameUpdate();
    void onMoveSuccess();

    //��ʼ��
    void initAnimation(animationType animType);
    //���Ŷ���
    void playAnimation(int x, int y);
private:
    //��������
    void createAnimation(const vector<wstring>& filenames);
    //��mapʹ�������ͺ͸ö�������
    map<animationType, vector<IMAGE>> animations;
    //���ڴ洢��Ҫ���ŵĶ�������
    animationType finalType;
    //����ѭ��������һ������
    int i;
};