#include "LevelManager.h"
#include <unordered_set>

// 显示碰撞区域，参数为碰撞区域的位置和颜色
void ShowCollide(Utils::Rect address, int color)
{
	setlinecolor(color);  // 设置线条颜色
	rectangle((int)address.posx, (int)address.posy,
		(int)address.posx + (int)address.width,
		(int)address.posy + (int)address.height);  // 绘制矩形，表示碰撞区域
	setlinecolor(WHITE);  // 将线条颜色设置回白色
}

// 通知UI，参数为UI对象，是否有消息，以及消息内容
void NoticeUI(MonoObject* obj, bool hasMessage, ExMessage msg)
{
	if (hasMessage) obj->onGetMessage(msg);  // 如果有消息，则调用对象的onGetMessage方法处理消息
	obj->onFrameUpdate();  // 调用对象的onFrameUpdate方法更新帧
}

// 获取LevelManager的单例
LevelManager& LevelManager::GetInstance()
{
	static LevelManager m_Instance;  // 定义一个静态的LevelManager实例
	return m_Instance;  // 返回这个实例
}

// 添加对象，参数为要添加的对象
void LevelManager::AddObject(MonoObject* obj)
{
	m_activeObjects.insert(obj);  // 将对象添加到活动对象集合中
}

// 删除对象，参数为要删除的对象
void LevelManager::DeleteObject(MonoObject* obj)
{
	m_deletingObjects.push(obj);  // 将对象添加到待删除对象队列中
}

// 运行LevelManager
void LevelManager::Run()
{
	ClearDeletingObjects();  // 清除待删除的对象
	ExMessage msg;  // 定义一个消息
	bool hasMessage = peekmessage(&msg);  // 检查是否有消息
	set<MonoObject*> UIObjects;  // 定义一个UI对象集合
	ProcessActiveObjects(hasMessage, msg, UIObjects);  // 处理活动对象
	noticeMove();  // 通知移动效果
	noticeGravity();  // 通知重力效果
	ProcessUIObjects(hasMessage, msg, UIObjects);  // 最后处理UI对象
}
// 清除待删除的对象
void LevelManager::ClearDeletingObjects()
{
	// 创建一个无序集合来存储已经删除的对象
	std::unordered_set<MonoObject*> deletedObjects;
	// 当待删除对象队列不为空时
	while (!m_deletingObjects.empty())
	{
		// 获取队列中的第一个对象
		MonoObject* obj = m_deletingObjects.front();
		// 从队列中移除这个对象
		m_deletingObjects.pop();
		// 检查对象是否已经被删除
		if (deletedObjects.find(obj) == deletedObjects.end()) {
			// 如果活动对象集合中存在这个对象
			if (m_activeObjects.find(obj) != m_activeObjects.end()) {
				// 从活动对象集合中删除这个对象
				m_activeObjects.erase(obj);
			}
			// 删除对象
			delete obj;
			// 将对象添加到已删除对象的集合中
			deletedObjects.insert(obj);
		}
	}
}

// 处理活动对象，参数为是否有消息，消息内容，以及UI对象集合
void LevelManager::ProcessActiveObjects(bool hasMessage, ExMessage& msg, set<MonoObject*>& UIObjects)
{
	for (auto& obj : m_activeObjects) {  // 遍历活动对象集合
		if (obj->type == UI)  // 如果对象类型为UI
		{
			UIObjects.insert(obj);  // 将对象添加到UI对象集合中
			continue;  // 跳过当前循环，处理下一个对象
		}
		if (hasMessage) noticeMessage(obj, &msg);  // 如果有消息，则通知对象处理消息
		obj->onFrameUpdate();  // 调用对象的onFrameUpdate方法更新帧
		if (obj->vx != 0 || obj->vy != 0) m_moveingObjects.push(obj);  // 如果对象有速度，则将对象添加到移动对象队列中
		if (obj->useGravity)  // 如果对象受重力影响
		{
			m_fallingObjects[obj] += Gravity / Sceneconfig::GetInstance()->MaxFrame;  // 更新对象的下落速度
		}
		else m_fallingObjects.erase(obj);  // 否则，从下落对象集合中删除这个对象
		if (debugModel)  // 如果处于调试模式
		{
			if (!obj->canThrough) ShowCollide(obj->body, RED);  // 如果对象不能穿透，则显示红色的碰撞区域
			else ShowCollide(obj->body, GREEN);  // 否则，显示绿色的碰撞区域
		}
	}
}

// 处理UI对象，参数为是否有消息，消息内容，以及UI对象集合
void LevelManager::ProcessUIObjects(bool hasMessage, ExMessage& msg, set<MonoObject*>& UIObjects)
{
	for (auto& obj : UIObjects)  // 遍历UI对象集合
	{
		NoticeUI(obj, hasMessage, msg);  // 通知UI对象处理消息和更新帧
	}
}

// 通知消息，参数为要通知的对象，以及消息内容
void LevelManager::noticeMessage(MonoObject* obj, ExMessage* msg)
{
	obj->onGetMessage(*msg);  // 调用对象的onGetMessage方法处理消息
}
// 通知移动
void LevelManager::noticeMove()
{
	while (!m_moveingObjects.empty())  // 当移动对象队列不为空时
	{
		MonoObject* obj = m_moveingObjects.front();  // 获取队列中的第一个对象
		m_moveingObjects.pop();  // 从队列中移除这个对象
		processObjectMovement(obj);  // 处理对象的移动
	}
	noticeCrash();  // 处理并通知碰撞效果
}

// 处理对象的移动，参数为要移动的对象
void LevelManager::processObjectMovement(MonoObject* obj)
{
	float x = obj->vx / Sceneconfig::GetInstance()->MaxFrame;  // 计算对象在x方向上的移动距离
	float y = obj->vy / Sceneconfig::GetInstance()->MaxFrame;  // 计算对象在y方向上的移动距离
	Utils::Rect address = Utils::Rect{ obj->body.posx + x,obj->body.posy + y ,obj->body.width,obj->body.height };  // 计算对象移动后的位置
	vector<MonoObject*> crashObjs = caculateCrash(address);  // 计算碰撞的对象
	MonoObject* crashObj_x = findCrashObject(crashObjs, obj, address, true);  // 找到在x方向上碰撞的对象
	MonoObject* crashObj_y = findCrashObject(crashObjs, obj, address, false);  // 找到在y方向上碰撞的对象
	processCrashObjects(obj, crashObj_x, crashObj_y);  // 处理碰撞的对象
	if (crashObj_x == nullptr && crashObj_y == nullptr)  // 如果没有碰撞的对象
	{
		Utils::Rect position = obj->body;
		position.posx += x;
		position.posy += y;
		obj->body = position;  // 更新对象的位置
		obj->onMoveSuccess();  // 调用对象的onMoveSuccess方法
	}
}

// 找到碰撞的第一个对象，参数为碰撞的对象集合，目标对象，目标对象的位置，碰撞的方向
MonoObject* LevelManager::findCrashObject(vector<MonoObject*>& crashObjs, MonoObject* targetObj, Utils::Rect& address, bool isXDirection)
{
	MonoObject* crashObj = nullptr;  // 初始化碰撞的对象为null
	for (MonoObject* it : crashObjs)  // 遍历碰撞的对象集合
	{
		if (it->GetHashID() == targetObj->GetHashID()) continue;  // 如果对象的哈希ID等于目标对象的哈希ID，则跳过当前循环
		if (crashObj == nullptr ||  // 如果碰撞的对象为null，或者
			abs((isXDirection ? crashObj->body.posx : crashObj->body.posy) - (isXDirection ? address.posx : address.posy))  // 碰撞的对象在对应方向上的位置与目标对象的位置的差的绝对值
			< abs((isXDirection ? it->body.posx : it->body.posy) - (isXDirection ? address.posx : address.posy)))  // 小于当前对象在对应方向上的位置与目标对象的位置的差的绝对值
		{
			crashObj = it;  // 则更新碰撞的对象为当前对象
		}
	}
	return crashObj;  // 返回碰撞的对象
}

// 处理碰撞的对象，参数为在x方向和y方向上碰撞到的对象
void LevelManager::processCrashObjects(MonoObject* obj, MonoObject* crashObj_x, MonoObject* crashObj_y)
{
	if (crashObj_x != nullptr)  // 如果在x方向上有碰撞的对象
	{
		// 判断谁撞到了谁
		m_crashObjects[make_pair(obj, crashObj_x)] = true;  
		if (!obj->canThrough) m_crashObjects[make_pair(crashObj_x, obj)] = true;  
	}
	if (crashObj_y != nullptr)  // 如果在y方向上有碰撞的对象
	{
		m_crashObjects[make_pair(obj, crashObj_y)] = true;  // 则将对象和碰撞的对象添加到碰撞对象集合中
		if (!obj->canThrough) m_crashObjects[make_pair(crashObj_y, obj)] = true;  // 如果对象不能穿透，则将碰撞的对象和对象添加到碰撞对象集合中
	}
}

// 计算碰撞，参数为一个矩形区域
vector<MonoObject*> LevelManager::caculateCrash(Utils::Rect address)
{
	vector<MonoObject*> crashObjs;  // 初始化碰撞对象集合
	for (MonoObject* obj : m_activeObjects) {  // 遍历活动对象集合
		if (!obj->canThrough && Utils::CrossLine(obj->body, address))  // 如果对象不能穿透，并且对象的体积与给定的矩形区域有交叉
		{
			crashObjs.push_back(obj);  // 则将对象添加到碰撞对象集合中
		}
	}
	return crashObjs;  // 返回碰撞对象集合
}

// 获取所有对象
vector<MonoObject*> LevelManager::getAllObjects()
{
	vector<MonoObject*> rev;  // 初始化返回的对象集合
	for (MonoObject* obj : m_activeObjects) {  // 遍历活动对象集合
		rev.push_back(obj);  // 将对象添加到返回的对象集合中
	}
	return rev;  // 返回对象集合
}

// 通知碰撞
void LevelManager::noticeCrash()
{
	for (auto& pair : m_crashObjects) {  // 遍历碰撞对象集合
		pair.first.first->onCrash(pair.first.second);  // 调用对象的onCrash方法处理碰撞
	}
	m_crashObjects.clear();  // 清空碰撞对象集合
}

// 通知重力
void LevelManager::noticeGravity()
{
	// 遍历下坠物体
	map<MonoObject*, float>::iterator it;
	for (it = m_fallingObjects.begin(); it != m_fallingObjects.end(); it++) {  
		// 计算当前帧重力速度导致的位移
		MonoObject* obj = it->first;  // 获取下坠物体
		float y = it->second / Sceneconfig::GetInstance()->MaxFrame;  // 计算下坠物体在y方向上的位移
		Utils::Rect address = Utils::Rect{ obj->body.posx,obj->body.posy + y ,obj->body.width,obj->body.height };  // 计算下坠物体移动后的位置
		vector<MonoObject*> crashObjs = caculateCrash(address);  // 计算碰撞的对象
		MonoObject* crashObj = findCrashObjectByGravity(crashObjs, obj, address);  // 找到由重力引起碰撞的对象
		if (crashObj != nullptr)  // 如果有碰撞的对象
		{
			it->second = 0;  // 则将下坠物体在y方向上的重力速度设置为0
			obj->onGroud(crashObj);  // 调用下坠物体的onGroud方法处理碰撞地面
		}
		else obj->body = address;  // 否则，更新下坠物体的位置
	}
}

// 找到由重力引起的碰撞的对象，参数为碰撞的对象集合，下坠物体，以及下坠物体的位置
MonoObject* LevelManager::findCrashObjectByGravity(vector<MonoObject*>& crashObjs, MonoObject* obj, Utils::Rect& address)
{
	MonoObject* crashObj = nullptr;  // 初始化碰撞的对象为null
	for (MonoObject* it : crashObjs)  // 遍历碰撞的对象集合
	{
		if (it->GetHashID() == obj->GetHashID()) continue;  // 如果对象的哈希ID等于下坠物体的哈希ID，则跳过当前循环
		if (crashObj == nullptr || abs(crashObj->body.posy - address.posy) < abs(it->body.posy - address.posy))  // 如果碰撞的对象为null，或者碰撞的对象在y方向上的位置与下坠物体的位置的差的绝对值小于当前对象在y方向上的位置与下坠物体的位置的差的绝对值
		{
			crashObj = it;  // 则更新碰撞的对象为当前对象
		}
	}
	return crashObj;  // 返回碰撞的对象
}