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
// 配置全局变量与静态信息
class Sceneconfig
{
public:
	// 代表当前绘制界面
	int flag = 0;
	// 代表当前关卡的名称
	const wchar_t* nowLevel;
	static Sceneconfig* GetInstance();
	/// <summary>
	/// 载入关卡
	/// </summary>
	void LoadLevel(const wchar_t* fileName);
	/// <summary>
	/// 加载当前关卡中的某一列
	/// </summary>
	void LoadObjects(int column);
	CameraObject* Camera;
	int MaxFrame = 120;
	float CellWidth = 60;
private:
	Sheet* levelSheet=nullptr;
	Sceneconfig();
};

