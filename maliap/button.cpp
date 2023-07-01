#include <iostream>
#include "easyx.h"
#include<graphics.h>
#include<stdio.h>
#include<vector>
#include<mmsystem.h>
#include <conio.h>
#include"button.h"
#include "head.h"
#include "SceneConfig.h"
#include "GameVoice.h"
using namespace Utils;
Button::Button()
{
	canThrough = true;
	type = UI;
}



void Button::onFrameUpdate()
{
	setlinecolor(RGB(255, 255, 255));
	setfillcolor(0xAAAAAA);
	setbkcolor(BLACK);
	setbkmode(TRANSPARENT);
	fillrectangle(body.posx, body.posy, body.posx + body.width, body.posy + body.height);
	int textWide = textwidth(m_name);
	int textHeight = textheight(m_name);
	outtextxy(body.posx + (body.width - textWide) / 2, body.posy + (body.height - textHeight) / 2, m_name);
	setbkcolor(WHITE);

}
void Button::onGetMessage(ExMessage message)
{
	if (message.message == WM_LBUTTONDOWN &&
		message.x >= body.posx && message.x <= body.posx + body.width &&
		message.y >= body.posy && message.y <= body.posy + body.height)
	{
		if (m_name == L"退出游戏")
		{
			GameAudio(11);
			//mciSendString(L"stop ./GameVoice/start.mp3", 0, 0, 0);
			closegraph();
		}
		else if (m_name == L"开始游戏")
		{
			GameAudio(11);
			mciSendString(L"stop ./GameVoice/start.mp3", 0, 0, 0);
			Sceneconfig::GetInstance()->flag = 1;
			Sceneconfig::GetInstance()->nowLevel = L"第一关";
			closegraph();
		}
		else if (m_name == L"返回菜单")
		{
			GameAudio(11);
			mciSendString(L"stop ./GameVoice/end.mp3", 0, 0, 0);
			Sceneconfig::GetInstance()->flag = 0;
			closegraph();
		}
		else if (m_name == L"选择关卡")
		{
			Sceneconfig::GetInstance()->flag = 4;
			closegraph();
		}
		else
		{
			GameAudio(11);
			mciSendString(L"stop ./GameVoice/start.mp3", 0, 0, 0);
			GameMusic(101);
			Sceneconfig::GetInstance()->flag = 1;
			Sceneconfig::GetInstance()->nowLevel = m_name;
			closegraph();
		}
	}
}