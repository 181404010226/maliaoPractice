#include "Window.h"
#include "Button.h"
#include "LevelManager.h"

void GameWindow::onCreate()
{
	
}


void GameWindow::menu()
{
	initgraph(body.width, body.height, EX_SHOWCONSOLE);
	loadimage(&img1, _T("./Image/开始界面背景.jpg"), body.width, body.height);
	// 设置线条颜色与填充颜色

	setlinecolor(RGB(255, 255, 255));
	setfillcolor(0xAAAAAA);
	// 创建按钮
	int size = 50, offset = 1.5;
	btn_play = CreateObject<Button>(
		Utils::Rect{ (float)body.width / 2 - size,
		(float)body.height / 2 - size / 2 + offset++ * size,(float)2 * size, (float)size });
	btn_play->m_name = L"开始游戏";
	btn_exit = CreateObject<Button>(
		Utils::Rect{ (float)body.width / 2 - size,
		(float)body.height / 2 - size / 2 + offset++ * size,(float)2 * size, (float)size });
	btn_exit->m_name = L"退出游戏";
	btn_set = CreateObject<Button>(
		Utils::Rect{ (float)body.width / 2 - size,
		(float)body.height / 2 - size / 2 + offset++ * size,(float)2 * size, (float)size });
	btn_set->m_name = L"选择关卡";
}

void GameWindow::gameover()
{
	initgraph(body.width, body.height, EX_SHOWCONSOLE);
	loadimage(&img1, _T("./Image/结束界面背景.jpg"), body.width, body.height);
	// 设置线条颜色与填充颜色

	setlinecolor(RGB(255, 255, 255));
	setfillcolor(0xAAAAAA);
	// 创建按钮
	int size = 50, offset = 1.5;
	btn_play = CreateObject<Button>(
		Utils::Rect{ (float)body.width / 2 - size,
		(float)body.height / 2 - size / 2 + offset++ * size,(float)2 * size, (float)size });
	btn_exit = CreateObject<Button>(
		Utils::Rect{ (float)body.width / 2 - size,
		(float)body.height / 2 - size / 2 + offset++ * size,(float)2 * size, (float)size });
	btn_play->m_name = L"返回菜单";
	btn_exit->m_name = L"退出游戏";
}

void GameWindow::onFrameUpdate()
{
	putimage(0, 0, &img1);
}

void GameWindow::gamewin()
{
	initgraph(body.width, body.height, EX_SHOWCONSOLE);
	loadimage(&img1, _T("./Image/像素背景2.jpg"), body.width, body.height);
	// 设置线条颜色与填充颜色

	setlinecolor(RGB(255, 255, 255));
	setfillcolor(0xAAAAAA);
	// 创建按钮
	int size = 50, offset = 1.5;
	btn_play = CreateObject<Button>(
		Utils::Rect{ (float)body.width / 2 - size,
		(float)body.height / 2 - size / 2 + offset++ * size,(float)2 * size, (float)size });
	btn_play->m_name = L"返回菜单";
}

void GameWindow::ChooseLevel()
{
	btn_play = CreateObject<Button>(
		Utils::Rect{ 450,0,(float)100, (float)50 });
	btn_play->m_name = L"返回菜单";
	initgraph(body.width, body.height, EX_SHOWCONSOLE);
	loadimage(&img1, _T("./Image/像素背景1.jpg"), body.width, body.height);
	// 设置线条颜色与填充颜色

	setlinecolor(RGB(255, 255, 255));
	setfillcolor(0xAAAAAA);
	// 创建按钮
	int size = 50, offset = 1.5;
	vector<string> level=Utils::FindAllLevel("./Map");
	int pos = 0;
	for (int i = 40; i < 600; i += 100)
	{
		for (int j = 200; j < 400; j += 50)
		{
			btn_play = CreateObject<Button>(
				Utils::Rect{ (float)i,(float)j,(float)2 * size, (float)size });
			btn_play->m_name = Utils::multiByteToWideChar(level[pos]);;
			pos++;
			if (pos >= level.size()) break;
		}
		if (pos >= level.size()) break;
	}
}

