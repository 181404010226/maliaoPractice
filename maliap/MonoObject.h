#pragma once
#include "head.h"
enum objectType {
	none,
	player,
	enemy,
	groud,
	effect,
	camera,
	UI
};


/// <summary>
/// 场景中的物体都要继承
/// </summary>
class MonoObject
{
public:
	int life = 5;
	int score = 0;
	// 代表物体类型
	objectType type=none;
	// 物体唯一编号
	int GetHashID();
	// 物体坐标与体积
	Utils::Rect body;
	// 物体移动速度，单位分别为m/s和kg。
	float vx = 0; 
	float vy = 0;
	float m = 1;
	// 能否穿越,为true情况不发生被动碰撞
	bool canThrough = false;
	// 是否启用物体受重力
	bool useGravity = false;
	// 物体创建时调用
	virtual void onCreate();
	// 物体发生碰撞时调用
	virtual void onCrash(MonoObject* collider);
	// 由重力系统引发碰撞时调用
	virtual void onGroud(MonoObject*collider);
	// 物体没有发生碰撞时调用
	virtual void onMoveSuccess();
	// 每帧调用
	virtual void onFrameUpdate();
	// 获取玩家输入的消息
	virtual void onGetMessage(ExMessage message);
	// 友元函数，用于修改哈希id
	template <typename T>
	friend T* CreateObject(Utils::Rect body);
	// 析构函数
	virtual ~MonoObject();
protected:
	MonoObject() = default;
private:
	int hashId = 0;
};

