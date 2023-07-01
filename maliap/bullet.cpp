#include "bullet.h"
#include<iostream>
#include <vector>
#include "LevelManager.h"
#include<algorithm>
#include "MonoObject.h"

bullet::bullet()
{
	type = enemy;
	vx = 15;
		 
}
void bullet::onCrash(MonoObject* collider)
{
	DestroyObject(this);

}
