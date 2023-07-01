#include "LevelManager.h"
// ͨ�÷���
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
	// ����m_moveingObjects����ȡ���ǵ��ٶ�v�����������ǵ�λ��
	while (!m_moveingObjects.empty())
	{
		MonoObject* obj = m_moveingObjects.front();
		m_moveingObjects.pop();
		// ���㵱ǰ֡λ��
		float x = obj->vx / Sceneconfig::GetInstance()->MaxFrame;
		float y = obj->vy / Sceneconfig::GetInstance()->MaxFrame;
		// ����ײ����˶�λ��
		Utils::Rect address = Utils::Rect{ obj->body.posx + x,obj->body.posy + y ,obj->body.width,obj->body.height };
		
		// �ҵ�x��y�����������ĵ�һ������
		vector<MonoObject*> crashObjs = caculateCrash(address);
		MonoObject* crashObj_x = nullptr;
		MonoObject* crashObj_y = nullptr;
		for (int i = 0; i < crashObjs.size(); i++)
		{
			MonoObject* it = crashObjs[i];
			if (it->GetHashID() == obj->GetHashID()) continue;
			if (crashObj_x== nullptr ||
				abs(crashObj_x->body.posx - address.posx) < abs(it->body.posx - address.posx))
			{
				crashObj_x = it;
			}
			if (crashObj_y == nullptr ||
				abs(crashObj_y->body.posy - address.posy) < abs(it->body.posy - address.posy))
			{
				crashObj_y = it;
			}
		}
		// ��ӵ���ײ��λ
		if (crashObj_x != nullptr)
		{
			m_crashObjects[make_pair(obj, crashObj_x)] = true;
			// �����ײ��λ���ɴ�Խ������ײ��λҲִ����ײ
			if (!obj->canThrough) m_crashObjects[make_pair(crashObj_x,obj)] = true;
		}
		if (crashObj_y != nullptr)
		{
			m_crashObjects[make_pair(obj, crashObj_y)] = true;
			if (!obj->canThrough) m_crashObjects[make_pair(crashObj_y, obj)] = true;
		}
		if (crashObj_x== nullptr && crashObj_y == nullptr)
		{
			Utils::Rect positon = obj->body;
			positon.posx += x;
			positon.posy += y;
			obj->body = positon;
			obj->onMoveSuccess();
		}
		
	}
	noticeCrash(); 
}



vector<MonoObject*> LevelManager::caculateCrash(Utils::Rect address)
{
	vector<MonoObject*> crashObjs;
	set<MonoObject*>::iterator it;
	for (it = m_activeObjects.begin(); it != m_activeObjects.end(); it++) {
		// �������в��ܴ�Խ���������ײ���
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
	// ���noticeMove�����˲��ɴ�Խ���壬֪ͨ����������ʲô
	map<pair<MonoObject*, MonoObject* >, bool>::iterator it;
	for (it =m_crashObjects.begin(); it != m_crashObjects.end(); it++) {
		it->first.first->onCrash(it->first.second);
	}
	m_crashObjects.clear();

}

void LevelManager::noticeGravity()
{
	// ������׹����
	map<MonoObject*, float>::iterator it;
	for (it = m_fallingObjects.begin(); it != m_fallingObjects.end(); it++) {
		// ���㵱ǰ֡�����ٶȵ��µ�λ��
		MonoObject* obj = it->first;
		float y = it->second / Sceneconfig::GetInstance()->MaxFrame;
		// ����ײ����˶�λ��
		Utils::Rect address = Utils::Rect{ obj->body.posx,obj->body.posy + y 
			,obj->body.width,obj->body.height };
		vector<MonoObject*> crashObjs = caculateCrash(address);
		// ���������������Ķ���
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
		// ֪ͨ�����������Ķ���
		if (crashObj!=nullptr)
		{
			it->second = 0;
			obj->onGroud(crashObj);
		}
		else obj->body = address;
	}
}
