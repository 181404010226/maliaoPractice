#include "CameraObject.h"
#include "SceneConfig.h"

CameraObject::CameraObject()
{
	type = camera;
}

void CameraObject::onCreate()
{
	canThrough = true;
	lastPos = body.posx/ Sceneconfig::GetInstance()->CellWidth;
	vx = 0.5* Sceneconfig::GetInstance()->CellWidth;
}

void CameraObject::onFrameUpdate()
{
	// 镜头示意
	rectangle((int)body.posx, (int)body.posy,(int)body.posx + (int)body.width, 600);
	// 向右移动
	if (body.posx/ Sceneconfig::GetInstance()->CellWidth - (float)lastPos > 1)
	{
		lastPos++;
		Sceneconfig::GetInstance()->LoadObjects(lastPos);
	}
	// 向做移动
	if (body.posx/ Sceneconfig::GetInstance()->CellWidth - (float)lastPos < -1)
	{
		lastPos--;
		Sceneconfig::GetInstance()->LoadObjects(lastPos);
	}
	// 删除所有不在相机指定范围内的物体
	vector<MonoObject*> objs = LevelManager::GetInstance().getAllObjects();
	for (int i = 0; i < objs.size(); i++)
	{
		MonoObject* obj = objs[i];
		if (obj->type == camera) continue;
		if (abs(obj->body.posx - body.posx) > 5* Sceneconfig::GetInstance()->CellWidth)
		{
			DestroyObject(obj);
		}
	}
}
