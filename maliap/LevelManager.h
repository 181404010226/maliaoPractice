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

class LevelManager
{
public:
    static LevelManager& GetInstance();
    void Run();
    vector<MonoObject*> caculateCrash(Utils::Rect address);
    vector<MonoObject*> getAllObjects();

    // 物体管理
    int hashID = 0;
    void AddObject(MonoObject* obj);
    void DeleteObject(MonoObject* obj);

private:
    LevelManager() = default;
    LevelManager(const LevelManager&) = delete;
    LevelManager& operator=(const LevelManager&) = delete;

    // Run函数重构
    void ClearDeletingObjects();
    void ProcessActiveObjects(bool hasMessage, ExMessage& msg, set<MonoObject*>& UIObjects);
    void ProcessUIObjects(bool hasMessage, ExMessage& msg, set<MonoObject*>& UIObjects);


    void noticeMessage(MonoObject* obj, ExMessage* msg);
    // 处理移动逻辑
    void noticeMove();
    void processObjectMovement(MonoObject* obj);
    MonoObject* findCrashObject(vector<MonoObject*>& crashObjs, MonoObject* targetObj, Utils::Rect& address, bool isXDirection);
    void processCrashObjects(MonoObject* obj, MonoObject* crashObj_x, MonoObject* crashObj_y);

    void noticeCrash();
    void noticeGravity();

    bool debugModel = false;
    float Gravity = 200;
    queue<MonoObject*> m_deletingObjects;
    set<MonoObject*> m_activeObjects;
    queue<MonoObject*> m_moveingObjects;
    map<MonoObject*, float> m_fallingObjects;
    map<MonoObject*, pair<float, float>> m_viewingObjects;
    map < pair<MonoObject*, MonoObject*>, bool> m_crashObjects;
};

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

inline void DestroyObject(MonoObject* destroyObject)
{
    LevelManager::GetInstance().DeleteObject(destroyObject);
}