// LevelManager.h
#pragma once
#include <iostream>
#include <map>
#include <queue>
#include <mutex>
#include <set>
#include <memory>
#include "MonoObject.h"
#include "head.h"
#include "SceneConfig.h"
using namespace std;

// 这段代码定义了一个名为LevelManager的类，该类用于管理游戏中的各种对象和事件。
//这段代码主要包含了游戏中的对象管理、碰撞检测、对象移动等功能。 
// 定义LevelManager类
class LevelManager
{
public:
    // 获取LevelManager的单例
    static LevelManager& GetInstance();
    // 运行LevelManager
    void Run();
    // 计算碰撞
    vector<MonoObject*> caculateCrash(Utils::Rect address);
    // 获取所有对象
    vector<MonoObject*> getAllObjects();
private:
    // 默认构造函数
    LevelManager() = default;
    // 删除复制构造函数
    LevelManager(const LevelManager&) = delete;
    // 删除赋值运算符
    LevelManager& operator=(const LevelManager&) = delete;
    // 添加对象
    void AddObject(MonoObject* obj);
    // 准备删除对象
    void DeleteObject(MonoObject* obj);
    // 清除待删除的对象的物理内存
    void ClearDeletingObjects();
    // 处理活动对象
    void ProcessActiveObjects(bool hasMessage, ExMessage& msg, set<MonoObject*>& UIObjects);
    // 处理UI对象
    void ProcessUIObjects(bool hasMessage, ExMessage& msg, set<MonoObject*>& UIObjects);
    // 通知玩家键盘或者鼠标信息
    void noticeMessage(MonoObject* obj, ExMessage* msg);
    // 处理移动逻辑
    void noticeMove();
    // 处理对象移动结果
    void processObjectMovement(MonoObject* obj);
    // 查找碰撞对象
    MonoObject* findCrashObject(vector<MonoObject*>& crashObjs, MonoObject* targetObj, Utils::Rect& address, bool isXDirection);
    // 处理碰撞对象
    void processCrashObjects(MonoObject* obj, MonoObject* crashObj_x, MonoObject* crashObj_y);
    // 通知碰撞或者重力效果
    void noticeCrash();
    // 查找重力碰撞对象
    MonoObject* findCrashObjectByGravity(vector<MonoObject*>& crashObjs, MonoObject* obj, Utils::Rect& address);
    // 通知重力
    void noticeGravity();
    // 调试模式
    const bool debugModel = false;
    // 哈希ID
    int hashID = 0;
    // 重力值
    const float Gravity = 200;
    // 待删除的对象队列
    queue<MonoObject*> m_deletingObjects;
    // 活动对象集合
    set<MonoObject*> m_activeObjects;
    // 移动对象队列
    queue<MonoObject*> m_moveingObjects;
    // 下落对象映射
    map<MonoObject*, float> m_fallingObjects;
    // 碰撞对象映射
    map < pair<MonoObject*, MonoObject*>, bool> m_crashObjects;
    // 创建对象的模板函数
    template <typename T>
    friend inline T* CreateObject(Utils::Rect body);
    // 销毁对象的函数
    friend inline void DestroyObject(MonoObject* destroyObject);
};

// 创建对象的模板函数实现
template <typename T>
inline T* CreateObject(Utils::Rect body)
{
    T* newObject = new T();
    LevelManager::GetInstance().AddObject(newObject);
    newObject->body = body;
    newObject->hashId = ++LevelManager::GetInstance().hashID;
    newObject->onCreate();
    return newObject;
}

// 销毁对象的函数实现
inline void DestroyObject(MonoObject* destroyObject)
{
    LevelManager::GetInstance().DeleteObject(destroyObject);
}