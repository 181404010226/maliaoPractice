#include "LevelManager.h"
// 通用方法
void ShowCollide(Utils::Rect address, int color)
{
	setlinecolor(color);
	rectangle((int)address.posx, (int)address.posy,
		(int)address.posx + (int)address.width,
		(int)address.posy + (int)address.height);
	setlinecolor(WHITE);
}

void NoticeUI(MonoObject* obj, bool hasMessage, ExMessage msg)
{
	if (hasMessage) obj->onGetMessage(msg);
	obj->onFrameUpdate();
}
// LevelManager.cpp

LevelManager& LevelManager::GetInstance()
{
	static LevelManager m_Instance;
	return m_Instance;
}

void LevelManager::AddObject(MonoObject* obj)
{
	m_activeObjects.insert(obj);
}

void LevelManager::DeleteObject(MonoObject* obj)
{
	m_deletingObjects.push(obj);
}




void LevelManager::Run()
{
	ClearDeletingObjects();
	ExMessage msg;
	bool hasMessage = peekmessage(&msg);
	set<MonoObject*> UIObjects;
	ProcessActiveObjects(hasMessage, msg, UIObjects);
	noticeMove();
	noticeGravity();
	ProcessUIObjects(hasMessage, msg, UIObjects);
}

void LevelManager::ClearDeletingObjects()
{
	while (!m_deletingObjects.empty())
	{
		MonoObject* obj = m_deletingObjects.front();
		m_deletingObjects.pop();
		m_activeObjects.erase(obj);
	}
}

void LevelManager::ProcessActiveObjects(bool hasMessage, ExMessage& msg, set<MonoObject*>& UIObjects)
{
	for (auto& obj : m_activeObjects) {
		if (obj->type == UI)
		{
			UIObjects.insert(obj);
			continue;
		}
		if (hasMessage) noticeMessage(obj, &msg);
		obj->onFrameUpdate();
		if (obj->vx != 0 || obj->vy != 0) m_moveingObjects.push(obj);
		if (obj->useGravity)
		{
			m_fallingObjects[obj] += Gravity / Sceneconfig::GetInstance()->MaxFrame;
		}
		else m_fallingObjects.erase(obj);
		if (debugModel)
		{
			if (!obj->canThrough) ShowCollide(obj->body, RED);
			else ShowCollide(obj->body, GREEN);
		}
	}
}

void LevelManager::ProcessUIObjects(bool hasMessage, ExMessage& msg, set<MonoObject*>& UIObjects)
{
	for (auto& obj : UIObjects)
	{
		NoticeUI(obj, hasMessage, msg);
	}
}
void LevelManager::noticeMessage(MonoObject* obj, ExMessage* msg)
{
	obj->onGetMessage(*msg);
}

void LevelManager::noticeMove()
{
	while (!m_moveingObjects.empty())
	{
		MonoObject* obj = m_moveingObjects.front();
		m_moveingObjects.pop();
		processObjectMovement(obj);
	}
	noticeCrash();
}

void LevelManager::processObjectMovement(MonoObject* obj)
{
	float x = obj->vx / Sceneconfig::GetInstance()->MaxFrame;
	float y = obj->vy / Sceneconfig::GetInstance()->MaxFrame;
	Utils::Rect address = Utils::Rect{ obj->body.posx + x,obj->body.posy + y ,obj->body.width,obj->body.height };
	vector<MonoObject*> crashObjs = caculateCrash(address);
	MonoObject* crashObj_x = findCrashObject(crashObjs, obj, address, true);
	MonoObject* crashObj_y = findCrashObject(crashObjs, obj, address, false);
	processCrashObjects(obj, crashObj_x, crashObj_y);
	if (crashObj_x == nullptr && crashObj_y == nullptr)
	{
		Utils::Rect position = obj->body;
		position.posx += x;
		position.posy += y;
		obj->body = position;
		obj->onMoveSuccess();
	}
}

MonoObject* LevelManager::findCrashObject(vector<MonoObject*>& crashObjs, MonoObject* targetObj, Utils::Rect& address, bool isXDirection)
{
	MonoObject* crashObj = nullptr;
	for (MonoObject* it : crashObjs)
	{
		if (it->GetHashID() == targetObj->GetHashID()) continue;
		if (crashObj == nullptr ||
			abs((isXDirection ? crashObj->body.posx : crashObj->body.posy) - (isXDirection ? address.posx : address.posy))
			< abs((isXDirection ? it->body.posx : it->body.posy) - (isXDirection ? address.posx : address.posy)))
		{
			crashObj = it;
		}
	}
	return crashObj;
}

void LevelManager::processCrashObjects(MonoObject* obj, MonoObject* crashObj_x, MonoObject* crashObj_y)
{
	if (crashObj_x != nullptr)
	{
		m_crashObjects[make_pair(obj, crashObj_x)]=true;
		if (!obj->canThrough) m_crashObjects[make_pair(crashObj_x, obj)]=true;
	}
	if (crashObj_y != nullptr)
	{
		m_crashObjects[make_pair(obj, crashObj_y)]=true;
		if (!obj->canThrough) m_crashObjects[make_pair(crashObj_y, obj)]=true;
	}
}


vector<MonoObject*> LevelManager::caculateCrash(Utils::Rect address)
{
	vector<MonoObject*> crashObjs;
	set<MonoObject*>::iterator it;
	for (it = m_activeObjects.begin(); it != m_activeObjects.end(); it++) {
		// 计算所有不能穿越的物体的碰撞情况
		if (!(*it)->canThrough && Utils::CrossLine((*it)->body, address))
		{
			crashObjs.push_back(*it);
		}
	}
	return crashObjs;
}

vector<MonoObject*> LevelManager::getAllObjects()
{
	vector<MonoObject*> rev;
	set<MonoObject*>::iterator it;
	for (it = m_activeObjects.begin(); it != m_activeObjects.end(); it++) {
		rev.push_back(*it);
	}
	return rev;
}


void LevelManager::noticeCrash()
{
	// 如果noticeMove碰到了不可穿越物体，通知他们碰到了什么
	map<pair<MonoObject*, MonoObject* >, bool>::iterator it;
	for (it =m_crashObjects.begin(); it != m_crashObjects.end(); it++) {
		it->first.first->onCrash(it->first.second);
	}
	m_crashObjects.clear();

}

void LevelManager::noticeGravity()
{
	// 遍历下坠物体
	map<MonoObject*, float>::iterator it;
	for (it = m_fallingObjects.begin(); it != m_fallingObjects.end(); it++) {
		// 计算当前帧重力速度导致的位移
		MonoObject* obj = it->first;
		float y = it->second / Sceneconfig::GetInstance()->MaxFrame;
		// 无碰撞情况运动位置
		Utils::Rect address = Utils::Rect{ obj->body.posx,obj->body.posy + y 
			,obj->body.width,obj->body.height };
		vector<MonoObject*> crashObjs = caculateCrash(address);
		// 计算重力触碰到的对象
		MonoObject* crashObj = nullptr;
		for (int i = 0; i < crashObjs.size(); i++)
		{
			MonoObject* it = crashObjs[i];
			if (it->GetHashID() == obj->GetHashID()) continue;
			if (crashObj == nullptr ||
				abs(crashObj->body.posy - address.posy) < abs(it->body.posy - address.posy))
			{
				crashObj = it;
			}
		}
		// 通知重力触碰到的对象
		if (crashObj!=nullptr)
		{
			it->second = 0;
			obj->onGroud(crashObj);
		}
		else obj->body = address;
	}
}
