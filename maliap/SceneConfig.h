#pragma once
#include "head.h"
#include <fstream>
#include <iostream>
#include "LevelManager.h"
#include <windows.h>
#include "libxl.h"
#include "testCube.h"
#include "CameraObject.h"
#include "head.h"
#include "Grass.h"
#include "Tree.h"
#include "House.h"
#include "Wmap.h"
#include "Cloud.h"
using namespace libxl;

using namespace std;
// ����ȫ�ֱ����뾲̬��Ϣ
class Sceneconfig
{
public:
	// ����ǰ���ƽ���
	int flag = 0;
	// ����ǰ�ؿ�������
	const wchar_t* nowLevel;
	static Sceneconfig* GetInstance();
	/// <summary>
	/// ����ؿ�
	/// </summary>
	void LoadLevel(const wchar_t* fileName);
	/// <summary>
	/// ���ص�ǰ�ؿ��е�ĳһ��
	/// </summary>
	void LoadObjects(int column);
	CameraObject* Camera;
	int MaxFrame = 120;
	float CellWidth = 60;
private:
	Sheet* levelSheet=nullptr;
	Sceneconfig();
};

