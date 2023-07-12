#include "LevelManager.h"
#include <unordered_set>

// ��ʾ��ײ���򣬲���Ϊ��ײ�����λ�ú���ɫ
void ShowCollide(Utils::Rect address, int color)
{
	setlinecolor(color);  // ����������ɫ
	rectangle((int)address.posx, (int)address.posy,
		(int)address.posx + (int)address.width,
		(int)address.posy + (int)address.height);  // ���ƾ��Σ���ʾ��ײ����
	setlinecolor(WHITE);  // ��������ɫ���ûذ�ɫ
}

// ֪ͨUI������ΪUI�����Ƿ�����Ϣ���Լ���Ϣ����
void NoticeUI(MonoObject* obj, bool hasMessage, ExMessage msg)
{
	if (hasMessage) obj->onGetMessage(msg);  // �������Ϣ������ö����onGetMessage����������Ϣ
	obj->onFrameUpdate();  // ���ö����onFrameUpdate��������֡
}

// ��ȡLevelManager�ĵ���
LevelManager& LevelManager::GetInstance()
{
	static LevelManager m_Instance;  // ����һ����̬��LevelManagerʵ��
	return m_Instance;  // �������ʵ��
}

// ��Ӷ��󣬲���ΪҪ��ӵĶ���
void LevelManager::AddObject(MonoObject* obj)
{
	m_activeObjects.insert(obj);  // ��������ӵ�����󼯺���
}

// ɾ�����󣬲���ΪҪɾ���Ķ���
void LevelManager::DeleteObject(MonoObject* obj)
{
	m_deletingObjects.push(obj);  // ��������ӵ���ɾ�����������
}

// ����LevelManager
void LevelManager::Run()
{
	ClearDeletingObjects();  // �����ɾ���Ķ���
	ExMessage msg;  // ����һ����Ϣ
	bool hasMessage = peekmessage(&msg);  // ����Ƿ�����Ϣ
	set<MonoObject*> UIObjects;  // ����һ��UI���󼯺�
	ProcessActiveObjects(hasMessage, msg, UIObjects);  // ��������
	noticeMove();  // ֪ͨ�ƶ�Ч��
	noticeGravity();  // ֪ͨ����Ч��
	ProcessUIObjects(hasMessage, msg, UIObjects);  // �����UI����
}
// �����ɾ���Ķ���
void LevelManager::ClearDeletingObjects()
{
	// ����һ�����򼯺����洢�Ѿ�ɾ���Ķ���
	std::unordered_set<MonoObject*> deletedObjects;
	// ����ɾ��������в�Ϊ��ʱ
	while (!m_deletingObjects.empty())
	{
		// ��ȡ�����еĵ�һ������
		MonoObject* obj = m_deletingObjects.front();
		// �Ӷ������Ƴ��������
		m_deletingObjects.pop();
		// �������Ƿ��Ѿ���ɾ��
		if (deletedObjects.find(obj) == deletedObjects.end()) {
			// �������󼯺��д����������
			if (m_activeObjects.find(obj) != m_activeObjects.end()) {
				// �ӻ���󼯺���ɾ���������
				m_activeObjects.erase(obj);
			}
			// ɾ������
			delete obj;
			// ��������ӵ���ɾ������ļ�����
			deletedObjects.insert(obj);
		}
	}
}

// �������󣬲���Ϊ�Ƿ�����Ϣ����Ϣ���ݣ��Լ�UI���󼯺�
void LevelManager::ProcessActiveObjects(bool hasMessage, ExMessage& msg, set<MonoObject*>& UIObjects)
{
	for (auto& obj : m_activeObjects) {  // ��������󼯺�
		if (obj->type == UI)  // �����������ΪUI
		{
			UIObjects.insert(obj);  // ��������ӵ�UI���󼯺���
			continue;  // ������ǰѭ����������һ������
		}
		if (hasMessage) noticeMessage(obj, &msg);  // �������Ϣ����֪ͨ��������Ϣ
		obj->onFrameUpdate();  // ���ö����onFrameUpdate��������֡
		if (obj->vx != 0 || obj->vy != 0) m_moveingObjects.push(obj);  // ����������ٶȣ��򽫶�����ӵ��ƶ����������
		if (obj->useGravity)  // �������������Ӱ��
		{
			m_fallingObjects[obj] += Gravity / Sceneconfig::GetInstance()->MaxFrame;  // ���¶���������ٶ�
		}
		else m_fallingObjects.erase(obj);  // ���򣬴�������󼯺���ɾ���������
		if (debugModel)  // ������ڵ���ģʽ
		{
			if (!obj->canThrough) ShowCollide(obj->body, RED);  // ��������ܴ�͸������ʾ��ɫ����ײ����
			else ShowCollide(obj->body, GREEN);  // ������ʾ��ɫ����ײ����
		}
	}
}

// ����UI���󣬲���Ϊ�Ƿ�����Ϣ����Ϣ���ݣ��Լ�UI���󼯺�
void LevelManager::ProcessUIObjects(bool hasMessage, ExMessage& msg, set<MonoObject*>& UIObjects)
{
	for (auto& obj : UIObjects)  // ����UI���󼯺�
	{
		NoticeUI(obj, hasMessage, msg);  // ֪ͨUI��������Ϣ�͸���֡
	}
}

// ֪ͨ��Ϣ������ΪҪ֪ͨ�Ķ����Լ���Ϣ����
void LevelManager::noticeMessage(MonoObject* obj, ExMessage* msg)
{
	obj->onGetMessage(*msg);  // ���ö����onGetMessage����������Ϣ
}
// ֪ͨ�ƶ�
void LevelManager::noticeMove()
{
	while (!m_moveingObjects.empty())  // ���ƶ�������в�Ϊ��ʱ
	{
		MonoObject* obj = m_moveingObjects.front();  // ��ȡ�����еĵ�һ������
		m_moveingObjects.pop();  // �Ӷ������Ƴ��������
		processObjectMovement(obj);  // ���������ƶ�
	}
	noticeCrash();  // ����֪ͨ��ײЧ��
}

// ���������ƶ�������ΪҪ�ƶ��Ķ���
void LevelManager::processObjectMovement(MonoObject* obj)
{
	float x = obj->vx / Sceneconfig::GetInstance()->MaxFrame;  // ���������x�����ϵ��ƶ�����
	float y = obj->vy / Sceneconfig::GetInstance()->MaxFrame;  // ���������y�����ϵ��ƶ�����
	Utils::Rect address = Utils::Rect{ obj->body.posx + x,obj->body.posy + y ,obj->body.width,obj->body.height };  // ��������ƶ����λ��
	vector<MonoObject*> crashObjs = caculateCrash(address);  // ������ײ�Ķ���
	MonoObject* crashObj_x = findCrashObject(crashObjs, obj, address, true);  // �ҵ���x��������ײ�Ķ���
	MonoObject* crashObj_y = findCrashObject(crashObjs, obj, address, false);  // �ҵ���y��������ײ�Ķ���
	processCrashObjects(obj, crashObj_x, crashObj_y);  // ������ײ�Ķ���
	if (crashObj_x == nullptr && crashObj_y == nullptr)  // ���û����ײ�Ķ���
	{
		Utils::Rect position = obj->body;
		position.posx += x;
		position.posy += y;
		obj->body = position;  // ���¶����λ��
		obj->onMoveSuccess();  // ���ö����onMoveSuccess����
	}
}

// �ҵ���ײ�ĵ�һ�����󣬲���Ϊ��ײ�Ķ��󼯺ϣ�Ŀ�����Ŀ������λ�ã���ײ�ķ���
MonoObject* LevelManager::findCrashObject(vector<MonoObject*>& crashObjs, MonoObject* targetObj, Utils::Rect& address, bool isXDirection)
{
	MonoObject* crashObj = nullptr;  // ��ʼ����ײ�Ķ���Ϊnull
	for (MonoObject* it : crashObjs)  // ������ײ�Ķ��󼯺�
	{
		if (it->GetHashID() == targetObj->GetHashID()) continue;  // �������Ĺ�ϣID����Ŀ�����Ĺ�ϣID����������ǰѭ��
		if (crashObj == nullptr ||  // �����ײ�Ķ���Ϊnull������
			abs((isXDirection ? crashObj->body.posx : crashObj->body.posy) - (isXDirection ? address.posx : address.posy))  // ��ײ�Ķ����ڶ�Ӧ�����ϵ�λ����Ŀ������λ�õĲ�ľ���ֵ
			< abs((isXDirection ? it->body.posx : it->body.posy) - (isXDirection ? address.posx : address.posy)))  // С�ڵ�ǰ�����ڶ�Ӧ�����ϵ�λ����Ŀ������λ�õĲ�ľ���ֵ
		{
			crashObj = it;  // �������ײ�Ķ���Ϊ��ǰ����
		}
	}
	return crashObj;  // ������ײ�Ķ���
}

// ������ײ�Ķ��󣬲���Ϊ��x�����y��������ײ���Ķ���
void LevelManager::processCrashObjects(MonoObject* obj, MonoObject* crashObj_x, MonoObject* crashObj_y)
{
	if (crashObj_x != nullptr)  // �����x����������ײ�Ķ���
	{
		// �ж�˭ײ����˭
		m_crashObjects[make_pair(obj, crashObj_x)] = true;  
		if (!obj->canThrough) m_crashObjects[make_pair(crashObj_x, obj)] = true;  
	}
	if (crashObj_y != nullptr)  // �����y����������ײ�Ķ���
	{
		m_crashObjects[make_pair(obj, crashObj_y)] = true;  // �򽫶������ײ�Ķ�����ӵ���ײ���󼯺���
		if (!obj->canThrough) m_crashObjects[make_pair(crashObj_y, obj)] = true;  // ��������ܴ�͸������ײ�Ķ���Ͷ�����ӵ���ײ���󼯺���
	}
}

// ������ײ������Ϊһ����������
vector<MonoObject*> LevelManager::caculateCrash(Utils::Rect address)
{
	vector<MonoObject*> crashObjs;  // ��ʼ����ײ���󼯺�
	for (MonoObject* obj : m_activeObjects) {  // ��������󼯺�
		if (!obj->canThrough && Utils::CrossLine(obj->body, address))  // ��������ܴ�͸�����Ҷ�������������ľ��������н���
		{
			crashObjs.push_back(obj);  // �򽫶�����ӵ���ײ���󼯺���
		}
	}
	return crashObjs;  // ������ײ���󼯺�
}

// ��ȡ���ж���
vector<MonoObject*> LevelManager::getAllObjects()
{
	vector<MonoObject*> rev;  // ��ʼ�����صĶ��󼯺�
	for (MonoObject* obj : m_activeObjects) {  // ��������󼯺�
		rev.push_back(obj);  // ��������ӵ����صĶ��󼯺���
	}
	return rev;  // ���ض��󼯺�
}

// ֪ͨ��ײ
void LevelManager::noticeCrash()
{
	for (auto& pair : m_crashObjects) {  // ������ײ���󼯺�
		pair.first.first->onCrash(pair.first.second);  // ���ö����onCrash����������ײ
	}
	m_crashObjects.clear();  // �����ײ���󼯺�
}

// ֪ͨ����
void LevelManager::noticeGravity()
{
	// ������׹����
	map<MonoObject*, float>::iterator it;
	for (it = m_fallingObjects.begin(); it != m_fallingObjects.end(); it++) {  
		// ���㵱ǰ֡�����ٶȵ��µ�λ��
		MonoObject* obj = it->first;  // ��ȡ��׹����
		float y = it->second / Sceneconfig::GetInstance()->MaxFrame;  // ������׹������y�����ϵ�λ��
		Utils::Rect address = Utils::Rect{ obj->body.posx,obj->body.posy + y ,obj->body.width,obj->body.height };  // ������׹�����ƶ����λ��
		vector<MonoObject*> crashObjs = caculateCrash(address);  // ������ײ�Ķ���
		MonoObject* crashObj = findCrashObjectByGravity(crashObjs, obj, address);  // �ҵ�������������ײ�Ķ���
		if (crashObj != nullptr)  // �������ײ�Ķ���
		{
			it->second = 0;  // ����׹������y�����ϵ������ٶ�����Ϊ0
			obj->onGroud(crashObj);  // ������׹�����onGroud����������ײ����
		}
		else obj->body = address;  // ���򣬸�����׹�����λ��
	}
}

// �ҵ��������������ײ�Ķ��󣬲���Ϊ��ײ�Ķ��󼯺ϣ���׹���壬�Լ���׹�����λ��
MonoObject* LevelManager::findCrashObjectByGravity(vector<MonoObject*>& crashObjs, MonoObject* obj, Utils::Rect& address)
{
	MonoObject* crashObj = nullptr;  // ��ʼ����ײ�Ķ���Ϊnull
	for (MonoObject* it : crashObjs)  // ������ײ�Ķ��󼯺�
	{
		if (it->GetHashID() == obj->GetHashID()) continue;  // �������Ĺ�ϣID������׹����Ĺ�ϣID����������ǰѭ��
		if (crashObj == nullptr || abs(crashObj->body.posy - address.posy) < abs(it->body.posy - address.posy))  // �����ײ�Ķ���Ϊnull��������ײ�Ķ�����y�����ϵ�λ������׹�����λ�õĲ�ľ���ֵС�ڵ�ǰ������y�����ϵ�λ������׹�����λ�õĲ�ľ���ֵ
		{
			crashObj = it;  // �������ײ�Ķ���Ϊ��ǰ����
		}
	}
	return crashObj;  // ������ײ�Ķ���
}