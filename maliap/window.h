#pragma once
#include <graphics.h>
#include "Button.h"
#include "Utils.h"
class GameWindow:public MonoObject
{
public:
	void onCreate();
	void menu();
	void gameover();
	void gamewin();
	void ChooseLevel();
	void onFrameUpdate();
private:
	IMAGE img1;
	Button* btn_play;
	Button* btn_exit;
	Button* btn_set;
};