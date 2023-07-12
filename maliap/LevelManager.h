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

// ��δ��붨����һ����ΪLevelManager���࣬�������ڹ�����Ϸ�еĸ��ֶ�����¼���
//��δ�����Ҫ��������Ϸ�еĶ��������ײ��⡢�����ƶ��ȹ��ܡ� 
// ����LevelManager��
class LevelManager
{
public:
    // ��ȡLevelManager�ĵ���
    static LevelManager& GetInstance();
    // ����LevelManager
    void Run();
    // ������ײ
    vector<MonoObject*> caculateCrash(Utils::Rect address);
    // ��ȡ���ж���
    vector<MonoObject*> getAllObjects();
private:
    // Ĭ�Ϲ��캯��
    LevelManager() = default;
    // ɾ�����ƹ��캯��
    LevelManager(const LevelManager&) = delete;
    // ɾ����ֵ�����
    LevelManager& operator=(const LevelManager&) = delete;
    // ��Ӷ���
    void AddObject(MonoObject* obj);
    // ׼��ɾ������
    void DeleteObject(MonoObject* obj);
    // �����ɾ���Ķ���������ڴ�
    void ClearDeletingObjects();
    // ��������
    void ProcessActiveObjects(bool hasMessage, ExMessage& msg, set<MonoObject*>& UIObjects);
    // ����UI����
    void ProcessUIObjects(bool hasMessage, ExMessage& msg, set<MonoObject*>& UIObjects);
    // ֪ͨ��Ҽ��̻��������Ϣ
    void noticeMessage(MonoObject* obj, ExMessage* msg);
    // �����ƶ��߼�
    void noticeMove();
    // ��������ƶ����
    void processObjectMovement(MonoObject* obj);
    // ������ײ����
    MonoObject* findCrashObject(vector<MonoObject*>& crashObjs, MonoObject* targetObj, Utils::Rect& address, bool isXDirection);
    // ������ײ����
    void processCrashObjects(MonoObject* obj, MonoObject* crashObj_x, MonoObject* crashObj_y);
    // ֪ͨ��ײ��������Ч��
    void noticeCrash();
    // ����������ײ����
    MonoObject* findCrashObjectByGravity(vector<MonoObject*>& crashObjs, MonoObject* obj, Utils::Rect& address);
    // ֪ͨ����
    void noticeGravity();
    // ����ģʽ
    const bool debugModel = false;
    // ��ϣID
    int hashID = 0;
    // ����ֵ
    const float Gravity = 200;
    // ��ɾ���Ķ������
    queue<MonoObject*> m_deletingObjects;
    // ����󼯺�
    set<MonoObject*> m_activeObjects;
    // �ƶ��������
    queue<MonoObject*> m_moveingObjects;
    // �������ӳ��
    map<MonoObject*, float> m_fallingObjects;
    // ��ײ����ӳ��
    map < pair<MonoObject*, MonoObject*>, bool> m_crashObjects;
    // ���������ģ�庯��
    template <typename T>
    friend inline T* CreateObject(Utils::Rect body);
    // ���ٶ���ĺ���
    friend inline void DestroyObject(MonoObject* destroyObject);
};

// ���������ģ�庯��ʵ��
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

// ���ٶ���ĺ���ʵ��
inline void DestroyObject(MonoObject* destroyObject)
{
    LevelManager::GetInstance().DeleteObject(destroyObject);
}