#define _CRT_SECURE_NO_WARNINGS 1
#include <easyx.h>
#include "LevelManager.h"
#include "head.h"
#include "testWall.h"
#include "testCube.h"
#include "SceneConfig.h"
#include <time.h>
#include "window.h"
#include"Bat.h"
#include "Player.h"
#include "Ghost.h"
#include "coin.h"
#include "zombie.h"

void clearAllObject()
{
	vector<MonoObject*> objs = LevelManager::GetInstance().getAllObjects();
	for (int i = 0; i < objs.size(); i++) DestroyObject(objs[i]);
}

void InitMenu()
{
	clearAllObject();
	GameWindow* window=CreateObject<GameWindow>(Utils::Rect{ 0,0,640, 480 });
	window->menu();
}

void GameOver()
{
	clearAllObject();
	GameWindow* window = CreateObject<GameWindow>(Utils::Rect{ 0,0,640, 480 });
	window->gameover();
}

void GameWin()
{
	clearAllObject();
	GameWindow* window = CreateObject<GameWindow>(Utils::Rect{ 0,0,640, 480 });
	window->gamewin();
}

void ChooseLevel()
{
	clearAllObject();
	GameWindow* window = CreateObject<GameWindow>(Utils::Rect{ 0,0,640, 480 });
	window->ChooseLevel();
}



void InitGame()
{
	clearAllObject();
	initgraph(1200, 900, EX_SHOWCONSOLE);
	cleardevice();
	wchar_t name[100];
	wcscpy(name, L"./Map/"); //������Ҫ������wcs�������롣
	wcscat(name, Sceneconfig::GetInstance()->nowLevel);
	wcscat(name, L".xlsx");
	Sceneconfig::GetInstance()->LoadLevel(name);
	// ��������ǽ
	CreateObject<testWall>(Utils::Rect{ -10,300,10,1200 });
	CreateObject<testWall>(Utils::Rect{ 1200,0,10,1200 });
	// ���ذ�ť
	Button* btn = CreateObject<Button>(
		Utils::Rect{ 600,0,(float)100, (float)50 });
	btn->m_name = L"���ز˵�";

}

int main(void)
{
	InitMenu();
	GameMusic(101);
	BeginBatchDraw();
	// ���ڿ���ÿ�����֡
	clock_t lastFrame = clock();
	int frameCnt = 0;
	int lastflag = 0;
	while (1)
	{
		if (Sceneconfig::GetInstance()->flag != lastflag)
		{
			if (Sceneconfig::GetInstance()->flag == 0) InitMenu();
			if (Sceneconfig::GetInstance()->flag == 1) InitGame();
			if (Sceneconfig::GetInstance()->flag == 2) GameOver();
			if (Sceneconfig::GetInstance()->flag == 3) GameWin();
			if (Sceneconfig::GetInstance()->flag == 4) ChooseLevel();
			lastflag = Sceneconfig::GetInstance()->flag;
		}
		// �̶�ʱ�������һ��
		if (clock() - lastFrame > frameCnt * 1000 / Sceneconfig::GetInstance()->MaxFrame)
		{
			
			FlushBatchDraw();//ֱ�������easyx������
			cleardevice();
			LevelManager::GetInstance().Run();
			frameCnt++;
			if (frameCnt == Sceneconfig::GetInstance()->MaxFrame)
			{
				frameCnt = 0;
				cout << Sceneconfig::GetInstance()->MaxFrame << "֡����ʱ��" << clock() - lastFrame << endl;
				lastFrame = clock();
			}
			// cout << "��" << frameCnt << "֡:" << clock() << endl;
		}
	}
	EndBatchDraw();//���Ƶ�easyx����
	return 0;
}
