#include "MonoObject.h"

int MonoObject::GetHashID()
{
	return hashId;
}

void MonoObject::onCreate()
{
}

void MonoObject::onCrash(MonoObject* collider)
{
}

void MonoObject::onGroud(MonoObject* collider)
{
}

void MonoObject::onMoveSuccess()
{
}

void MonoObject::onFrameUpdate()
{
}

void MonoObject::onGetMessage(ExMessage message)
{
}

MonoObject::~MonoObject()
{
}
