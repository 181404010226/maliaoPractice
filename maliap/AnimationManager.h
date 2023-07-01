#pragma once
#include "MonoObject.h"
#include<map>
#include<vector>
#include<easyx.h>
#include "tools.hpp"
using namespace std;

//动画类型
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

    //初始化
    void initAnimation(animationType animType);
    //播放动画
    void playAnimation(int x, int y);
private:
    //制作动画
    void createAnimation(const vector<wstring>& filenames);
    //用map使动画类型和该动画关联
    map<animationType, vector<IMAGE>> animations;
    //用于存储需要播放的动画类型
    animationType finalType;
    //用于循环动画的一个变量
    int i;
};