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
		mciSendString(L"open ./GameVoice/��ť.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/��ť.wav ", 0, 0, 0);
	}
	if (num == 12)
	{
		mciSendString(L"open ./GameVoice/����.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/����.wav ", 0, 0, 0);
	}
	if (num == 13)
	{
		mciSendString(L"open ./GameVoice/����1.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/����1.wav ", 0, 0, 0);
	}
	if (num == 14)
	{
		mciSendString(L"open ./GameVoice/����2.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/����2.wav ", 0, 0, 0);
	}
	if (num == 15)
	{
		mciSendString(L"open ./GameVoice/����.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/����.wav ", 0, 0, 0);
	}
	if (num == 16)
	{
		mciSendString(L"open ./GameVoice/��ɱ.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/��ɱ.wav ", 0, 0, 0);
	}
	if (num == 17)
	{
		mciSendString(L"open ./GameVoice/�ӷ�.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/�ӷ�.wav ", 0, 0, 0);
	}
	if (num == 18)
	{
		mciSendString(L"open ./GameVoice/��Ѫ1.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/��Ѫ1.wav ", 0, 0, 0);
	}
	if (num == 19)
	{
		mciSendString(L"open ./GameVoice/��Ѫ2.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/��Ѫ2.wav ", 0, 0, 0);
	}

	if (num == 20)
	{
		mciSendString(L"open ./GameVoice/��Ѫ3.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/��Ѫ3.wav ", 0, 0, 0);
	}

	if (num == 21)
	{
		mciSendString(L"open ./GameVoice/�з.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/�з.wav ", 0, 0, 0);
	}
	if (num == 22)
	{
		mciSendString(L"open ./GameVoice/��Ծ.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/��Ծ.wav ", 0, 0, 0);
	}
	if (num == 23)
	{
		mciSendString(L"open ./GameVoice/����.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/����.wav ", 0, 0, 0);
	}
	if (num == 25)
	{
		mciSendString(L"open ./GameVoice/����.wav ", 0, 0, 0);
		mciSendString(L"play ./GameVoice/����.wav ", 0, 0, 0);
	}

	

}


