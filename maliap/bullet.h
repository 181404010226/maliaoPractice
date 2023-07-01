#pragma once
#include "MonoObject.h"
class bullet :public MonoObject

{
public:
    bullet();
    void onCrash(MonoObject* collider);


};

