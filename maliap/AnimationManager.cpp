#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
	type = effect;
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::onCrash(MonoObject collider)
{
}

void AnimationManager::onFrameUpdate()
{
}

void AnimationManager::onMoveSuccess()
{
}
void AnimationManager::createAnimation(const vector<wstring>& imagenames)
{
	vector<IMAGE> images;
	for (const auto& filename : imagenames)
	{
		IMAGE image;
		loadimage(&image, filename.c_str());
		images.push_back(image);
	}
	animations[finalType] = images;
}
void AnimationManager::initAnimation(animationType animType)
{
	finalType = animType;
	switch (finalType)
	{
	case Man_walk:
		createAnimation({	L"Image/Animation/man1.png" ,L"Image/Animation/man1.png",L"Image/Animation/man1.png" ,L"Image/Animation/man1.png" ,L"Image/Animation/man1.png" ,L"Image/Animation/man1.png",
							L"Image/Animation/man2.png" ,L"Image/Animation/man2.png",L"Image/Animation/man2.png" ,L"Image/Animation/man2.png" ,L"Image/Animation/man2.png" ,L"Image/Animation/man2.png",
							L"Image/Animation/man3.png" ,L"Image/Animation/man3.png",L"Image/Animation/man3.png" ,L"Image/Animation/man3.png" ,L"Image/Animation/man3.png" ,L"Image/Animation/man3.png" ,
							L"Image/Animation/man4.png" ,L"Image/Animation/man4.png",L"Image/Animation/man4.png" ,L"Image/Animation/man4.png" ,L"Image/Animation/man4.png" ,L"Image/Animation/man4.png" });
		break;
	case DebuffMan_walk:
		createAnimation({	L"Image/Animation/mandebuff1.png",L"Image/Animation/mandebuff1.png",L"Image/Animation/mandebuff1.png",L"Image/Animation/mandebuff1.png",L"Image/Animation/mandebuff1.png",L"Image/Animation/mandebuff1.png",
							L"Image/Animation/mandebuff2.png",L"Image/Animation/mandebuff2.png",L"Image/Animation/mandebuff2.png",L"Image/Animation/mandebuff2.png",L"Image/Animation/mandebuff2.png",L"Image/Animation/mandebuff2.png",
							L"Image/Animation/mandebuff3.png",L"Image/Animation/mandebuff3.png",L"Image/Animation/mandebuff3.png",L"Image/Animation/mandebuff3.png",L"Image/Animation/mandebuff3.png",L"Image/Animation/mandebuff3.png",
							L"Image/Animation/mandebuff4.png",L"Image/Animation/mandebuff4.png",L"Image/Animation/mandebuff4.png",L"Image/Animation/mandebuff4.png",L"Image/Animation/mandebuff4.png",L"Image/Animation/mandebuff4.png" });

		break;

	case Pangxie_walk:
		createAnimation({	L"Image/Animation/ó¦Ð·1.png" ,L"Image/Animation/ó¦Ð·1.png" ,L"Image/Animation/ó¦Ð·1.png" ,L"Image/Animation/ó¦Ð·1.png" ,L"Image/Animation/ó¦Ð·1.png" ,L"Image/Animation/ó¦Ð·1.png",
							L"Image/Animation/ó¦Ð·2.png" ,L"Image/Animation/ó¦Ð·2.png" ,L"Image/Animation/ó¦Ð·2.png" ,L"Image/Animation/ó¦Ð·2.png" ,L"Image/Animation/ó¦Ð·2.png" ,L"Image/Animation/ó¦Ð·2.png",
							L"Image/Animation/ó¦Ð·3.png" ,L"Image/Animation/ó¦Ð·3.png" ,L"Image/Animation/ó¦Ð·3.png" ,L"Image/Animation/ó¦Ð·3.png" ,L"Image/Animation/ó¦Ð·3.png" ,L"Image/Animation/ó¦Ð·3.png", 
							L"Image/Animation/ó¦Ð·4.png", L"Image/Animation/ó¦Ð·4.png", L"Image/Animation/ó¦Ð·4.png", L"Image/Animation/ó¦Ð·4.png", L"Image/Animation/ó¦Ð·4.png", L"Image/Animation/ó¦Ð·4.png",
							L"Image/Animation/ó¦Ð·5.png", L"Image/Animation/ó¦Ð·5.png", L"Image/Animation/ó¦Ð·5.png", L"Image/Animation/ó¦Ð·5.png", L"Image/Animation/ó¦Ð·5.png", L"Image/Animation/ó¦Ð·5.png" });
		break;
	case Bat_fly:
		createAnimation({	L"Image/Animation/Bat1.png",L"Image/Animation/Bat1.png",L"Image/Animation/Bat1.png",L"Image/Animation/Bat1.png",L"Image/Animation/Bat1.png",L"Image/Animation/Bat1.png",
							L"Image/Animation/Bat2.png",L"Image/Animation/Bat2.png",L"Image/Animation/Bat2.png",L"Image/Animation/Bat2.png",L"Image/Animation/Bat2.png",L"Image/Animation/Bat2.png",
							L"Image/Animation/Bat3.png",L"Image/Animation/Bat3.png",L"Image/Animation/Bat3.png",L"Image/Animation/Bat3.png",L"Image/Animation/Bat3.png",L"Image/Animation/Bat3.png",
							L"Image/Animation/Bat4.png",L"Image/Animation/Bat4.png",L"Image/Animation/Bat4.png",L"Image/Animation/Bat4.png",L"Image/Animation/Bat4.png",L"Image/Animation/Bat4.png",
							L"Image/Animation/Bat5.png",L"Image/Animation/Bat5.png",L"Image/Animation/Bat5.png",L"Image/Animation/Bat5.png",L"Image/Animation/Bat5.png",L"Image/Animation/Bat5.png",
							L"Image/Animation/Bat6.png",L"Image/Animation/Bat6.png",L"Image/Animation/Bat6.png",L"Image/Animation/Bat6.png",L"Image/Animation/Bat6.png",L"Image/Animation/Bat6.png",
							L"Image/Animation/Bat7.png",L"Image/Animation/Bat7.png",L"Image/Animation/Bat7.png",L"Image/Animation/Bat7.png",L"Image/Animation/Bat7.png",L"Image/Animation/Bat7.png" });
		break;
	case Ghost_fly:
		createAnimation({	L"Image/Animation/ghost1.png",L"Image/Animation/ghost1.png",L"Image/Animation/ghost1.png",L"Image/Animation/ghost1.png",L"Image/Animation/ghost1.png",L"Image/Animation/ghost1.png",
							L"Image/Animation/ghost2.png",L"Image/Animation/ghost2.png",L"Image/Animation/ghost2.png",L"Image/Animation/ghost2.png",L"Image/Animation/ghost2.png",L"Image/Animation/ghost2.png",
							L"Image/Animation/ghost3.png",L"Image/Animation/ghost3.png",L"Image/Animation/ghost3.png",L"Image/Animation/ghost3.png",L"Image/Animation/ghost3.png",L"Image/Animation/ghost3.png",
							L"Image/Animation/ghost4.png",L"Image/Animation/ghost4.png",L"Image/Animation/ghost4.png",L"Image/Animation/ghost4.png",L"Image/Animation/ghost4.png",L"Image/Animation/ghost4.png",
							L"Image/Animation/ghost5.png",L"Image/Animation/ghost5.png",L"Image/Animation/ghost5.png",L"Image/Animation/ghost5.png",L"Image/Animation/ghost5.png",L"Image/Animation/ghost5.png",
							L"Image/Animation/ghost6.png",L"Image/Animation/ghost6.png",L"Image/Animation/ghost6.png",L"Image/Animation/ghost6.png",L"Image/Animation/ghost6.png",L"Image/Animation/ghost6.png",
							L"Image/Animation/ghost7.png",L"Image/Animation/ghost7.png",L"Image/Animation/ghost7.png",L"Image/Animation/ghost7.png",L"Image/Animation/ghost7.png",L"Image/Animation/ghost7.png"});
		break;
	case Pig_Idle:
		createAnimation({	L"Image/Animation/pigIdle1.png",L"Image/Animation/pigIdle1.png",L"Image/Animation/pigIdle1.png",L"Image/Animation/pigIdle1.png",L"Image/Animation/pigIdle1.png",L"Image/Animation/pigIdle1.png",
							L"Image/Animation/pigIdle2.png",L"Image/Animation/pigIdle2.png",L"Image/Animation/pigIdle2.png",L"Image/Animation/pigIdle2.png",L"Image/Animation/pigIdle2.png",L"Image/Animation/pigIdle2.png",
							L"Image/Animation/pigIdle3.png",L"Image/Animation/pigIdle3.png",L"Image/Animation/pigIdle3.png",L"Image/Animation/pigIdle3.png",L"Image/Animation/pigIdle3.png",L"Image/Animation/pigIdle3.png",
							L"Image/Animation/pigIdle4.png",L"Image/Animation/pigIdle4.png",L"Image/Animation/pigIdle4.png",L"Image/Animation/pigIdle4.png",L"Image/Animation/pigIdle4.png",L"Image/Animation/pigIdle4.png" });
			break;
	case Pig_Walk:
		createAnimation({	L"Image/Animation/pigWalk1.png",L"Image/Animation/pigWalk1.png",L"Image/Animation/pigWalk1.png",L"Image/Animation/pigWalk1.png",L"Image/Animation/pigWalk1.png",L"Image/Animation/pigWalk1.png",
							L"Image/Animation/pigWalk2.png",L"Image/Animation/pigWalk2.png",L"Image/Animation/pigWalk2.png",L"Image/Animation/pigWalk2.png",L"Image/Animation/pigWalk2.png",L"Image/Animation/pigWalk2.png",
							L"Image/Animation/pigWalk3.png",L"Image/Animation/pigWalk3.png",L"Image/Animation/pigWalk3.png",L"Image/Animation/pigWalk3.png",L"Image/Animation/pigWalk3.png",L"Image/Animation/pigWalk3.png",
							L"Image/Animation/pigWalk4.png",L"Image/Animation/pigWalk4.png",L"Image/Animation/pigWalk4.png",L"Image/Animation/pigWalk4.png",L"Image/Animation/pigWalk4.png",L"Image/Animation/pigWalk4.png",
							L"Image/Animation/pigWalk5.png",L"Image/Animation/pigWalk5.png",L"Image/Animation/pigWalk5.png",L"Image/Animation/pigWalk5.png",L"Image/Animation/pigWalk5.png",L"Image/Animation/pigWalk5.png",
							L"Image/Animation/pigWalk6.png",L"Image/Animation/pigWalk6.png",L"Image/Animation/pigWalk6.png",L"Image/Animation/pigWalk6.png",L"Image/Animation/pigWalk6.png",L"Image/Animation/pigWalk6.png",
							L"Image/Animation/pigWalk7.png",L"Image/Animation/pigWalk7.png",L"Image/Animation/pigWalk7.png",L"Image/Animation/pigWalk7.png",L"Image/Animation/pigWalk7.png",L"Image/Animation/pigWalk7.png",
							L"Image/Animation/pigWalk8.png",L"Image/Animation/pigWalk8.png",L"Image/Animation/pigWalk8.png",L"Image/Animation/pigWalk8.png",L"Image/Animation/pigWalk8.png",L"Image/Animation/pigWalk8.png" });
			break;
	case Coin_rotate:
		createAnimation({	L"Image/Animation/coin1.png",L"Image/Animation/coin1.png",L"Image/Animation/coin1.png",L"Image/Animation/coin1.png",L"Image/Animation/coin1.png",L"Image/Animation/coin1.png",
							L"Image/Animation/coin2.png",L"Image/Animation/coin2.png",L"Image/Animation/coin2.png",L"Image/Animation/coin2.png",L"Image/Animation/coin2.png",L"Image/Animation/coin2.png",
							L"Image/Animation/coin3.png",L"Image/Animation/coin3.png",L"Image/Animation/coin3.png",L"Image/Animation/coin3.png",L"Image/Animation/coin3.png",L"Image/Animation/coin3.png",
							L"Image/Animation/coin4.png",L"Image/Animation/coin4.png",L"Image/Animation/coin4.png",L"Image/Animation/coin4.png",L"Image/Animation/coin4.png",L"Image/Animation/coin4.png",
							L"Image/Animation/coin5.png",L"Image/Animation/coin5.png",L"Image/Animation/coin5.png",L"Image/Animation/coin5.png",L"Image/Animation/coin5.png",L"Image/Animation/coin5.png",
							L"Image/Animation/coin6.png",L"Image/Animation/coin6.png",L"Image/Animation/coin6.png",L"Image/Animation/coin6.png",L"Image/Animation/coin6.png",L"Image/Animation/coin6.png",
							L"Image/Animation/coin7.png",L"Image/Animation/coin7.png",L"Image/Animation/coin7.png",L"Image/Animation/coin7.png",L"Image/Animation/coin7.png",L"Image/Animation/coin7.png",
							L"Image/Animation/coin8.png",L"Image/Animation/coin8.png",L"Image/Animation/coin8.png",L"Image/Animation/coin8.png",L"Image/Animation/coin8.png",L"Image/Animation/coin8.png",
							L"Image/Animation/coin9.png",L"Image/Animation/coin9.png",L"Image/Animation/coin9.png",L"Image/Animation/coin9.png",L"Image/Animation/coin9.png",L"Image/Animation/coin9.png" });
		break;
	case Man_Idle:
		createAnimation({	L"Image/Animation/Idle1.png",L"Image/Animation/Idle1.png",L"Image/Animation/Idle1.png",L"Image/Animation/Idle1.png",L"Image/Animation/Idle1.png",L"Image/Animation/Idle1.png",
							L"Image/Animation/Idle2.png",L"Image/Animation/Idle2.png",L"Image/Animation/Idle2.png",L"Image/Animation/Idle2.png",L"Image/Animation/Idle2.png",L"Image/Animation/Idle2.png",
							L"Image/Animation/Idle3.png",L"Image/Animation/Idle3.png",L"Image/Animation/Idle3.png",L"Image/Animation/Idle3.png",L"Image/Animation/Idle3.png",L"Image/Animation/Idle3.png",
							L"Image/Animation/Idle4.png",L"Image/Animation/Idle4.png",L"Image/Animation/Idle4.png",L"Image/Animation/Idle4.png",L"Image/Animation/Idle4.png",L"Image/Animation/Idle4.png" });
		break;
	default:
		break;
	}
}

void AnimationManager::playAnimation(int x, int y)		
{
	auto it = animations.find(finalType);
	if (it == animations.end())
	{
		//cout << "ÎÞ¸Ã¶¯»­ÀàÐÍ" << endl;
		return;
	}
	else
	{
		//»æÖÆ¶¯»­
		drawImg(x, y, &(it->second[i]));
		i = (i + 1) % it->second.size();
	}
}
