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
/// �����е����嶼Ҫ�̳�
/// </summary>
class MonoObject
{
public:
	int life = 5;
	int score = 0;
	// ������������
	objectType type=none;
	// ����Ψһ���
	int GetHashID();
	// �������������
	Utils::Rect body;
	// �����ƶ��ٶȣ���λ�ֱ�Ϊm/s��kg��
	float vx = 0; 
	float vy = 0;
	float m = 1;
	// �ܷ�Խ,Ϊtrue���������������ײ
	bool canThrough = false;
	// �Ƿ���������������
	bool useGravity = false;
	// ���崴��ʱ����
	virtual void onCreate();
	// ���巢����ײʱ����
	virtual void onCrash(MonoObject* collider);
	// ������ϵͳ������ײʱ����
	virtual void onGroud(MonoObject*collider);
	// ����û�з�����ײʱ����
	virtual void onMoveSuccess();
	// ÿ֡����
	virtual void onFrameUpdate();
	// ��ȡ����������Ϣ
	virtual void onGetMessage(ExMessage message);
	// ��Ԫ�����������޸Ĺ�ϣid
	template <typename T>
	friend T* CreateObject(Utils::Rect body);
	// ��������
	virtual ~MonoObject();
protected:
	MonoObject() = default;
private:
	int hashId = 0;
};

