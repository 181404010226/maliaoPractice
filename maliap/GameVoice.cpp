#include"GameVoice.h"
#include<stdio.h>
#include<iostream>
#include<iostream>
#include<stdio.h>
#include<graphics.h>

#include<Windows.h>
#include<mmsystem.h>  

#include<string>
#pragma comment(lib,"winmm.lib")
using namespace std;
#include"GameVoice.h"

void GameMusic(int num)
{
	if (num == 0)
	{
		mciSendString(L"stop ./GameVoice/start.mp3", 0, 0, 0);
	}
	if (num == 100)
	{
		mciSendString(L"open ./GameVoice/start.mp3 ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/start.mp3", 0, 0, 0);
	}
	if (num == 101)
	{
		mciSendString(L"open ./GameVoice/Gaming.mp3 ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/Gaming.mp3 ", 0, 0, 0);
	}
	if (num == 102)
	{
		mciSendString(L"open ./GameVoice/end.mp3 ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/end.mp3 ", 0, 0, 0);
	}

}




void GameAudio(int num)
{
	
	if (num == 0)
	{
		mciSendString(L"stop music", 0, 0, 0);
	}

	if (num == 11)
	{
		mciSendString(L"open ./GameVoice/°´Å¥.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/°´Å¥.wav ", 0, 0, 0);
	}
	if (num == 12)
	{
		mciSendString(L"open ./GameVoice/òùòð.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/òùòð.wav ", 0, 0, 0);
	}
	if (num == 13)
	{
		mciSendString(L"open ./GameVoice/·¢Éä1.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/·¢Éä1.wav ", 0, 0, 0);
	}
	if (num == 14)
	{
		mciSendString(L"open ./GameVoice/·¢Éä2.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/·¢Éä2.wav ", 0, 0, 0);
	}
	if (num == 15)
	{
		mciSendString(L"open ./GameVoice/¸´»î.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/¸´»î.wav ", 0, 0, 0);
	}
	if (num == 16)
	{
		mciSendString(L"open ./GameVoice/»÷É±.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/»÷É±.wav ", 0, 0, 0);
	}
	if (num == 17)
	{
		mciSendString(L"open ./GameVoice/¼Ó·Ö.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/¼Ó·Ö.wav ", 0, 0, 0);
	}
	if (num == 18)
	{
		mciSendString(L"open ./GameVoice/¿ÛÑª1.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/¿ÛÑª1.wav ", 0, 0, 0);
	}
	if (num == 19)
	{
		mciSendString(L"open ./GameVoice/¿ÛÑª2.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/¿ÛÑª2.wav ", 0, 0, 0);
	}

	if (num == 20)
	{
		mciSendString(L"open ./GameVoice/¿ÛÑª3.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/¿ÛÑª3.wav ", 0, 0, 0);
	}

	if (num == 21)
	{
		mciSendString(L"open ./GameVoice/ó¦Ð·.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/ó¦Ð·.wav ", 0, 0, 0);
	}
	if (num == 22)
	{
		mciSendString(L"open ./GameVoice/ÌøÔ¾.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/ÌøÔ¾.wav ", 0, 0, 0);
	}
	if (num == 23)
	{
		mciSendString(L"open ./GameVoice/ÓÄÁé.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/ÓÄÁé.wav ", 0, 0, 0);
	}
	if (num == 25)
	{
		mciSendString(L"open ./GameVoice/ÕóÍö.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/ÕóÍö.wav ", 0, 0, 0);
	}

	

}


