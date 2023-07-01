#pragma once
#include <iostream>
#include "MonoObject.h"
using namespace std;
class Button :public MonoObject
{
public:
	Button();
	const wchar_t* m_name;
	void onFrameUpdate();
	void onGetMessage(ExMessage message);
	int check(ExMessage& message);
};
