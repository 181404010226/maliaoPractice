#include "Player.h"
#include <string>
#include<atlstr.h> 

Player::Player()
{

	loadimage(&love, (_T("./Image/heart.png")));
	useGravity = true;
	type = player;
	initAnimation(Man_Idle);//参数值Man_walk,DebuffMan_walk,Pig_Idle,Pig_Walk,Ghost_fly,Pangxie_walk,Bat_fly
	//initAnimation(Man_Idle);
	vx = 0, vy = 0;
}

void Player::onGetMessage(ExMessage message)//画面限制没写  自动落下
{

	if (canJump && !heated)
	{
		// 跳跃时增加推力
		if (message.message == WM_KEYDOWN && message.vkcode == 'W')
		{
			GameAudio(22);
			jump();
		}
	}
	// 左右移动
	if (message.message == WM_KEYDOWN)
	{
		if (message.vkcode == 'A') KEYA = true;
		if (message.vkcode == 'D') KEYD = true;
	}
	if (message.message == WM_KEYUP)
	{
		if (message.vkcode == 'A') KEYA = false;
		if (message.vkcode == 'D') KEYD = false;
	}
	if (!heated)
	{
		// 左右移动
		if (KEYA && !KEYD) vx = -100;
		if (!KEYA && KEYD) vx = 100;
		if (!KEYA && !KEYD) vx = 0;
	}
}


void Player::onFrameUpdate()
{
	if (body.posy > 1200 || life == 0)
	{
		GameMusic(102);
		Sceneconfig::GetInstance()->flag = 2;
	}

	playAnimation((int)body.posx, (int)body.posy);
	outtextxy(100, 0, L" 得分:");
	CString str;
	str.Format(_T("%d"), score);
	LPCTSTR pStr = LPCTSTR(str);
	outtextxy(150, 0, pStr);
	for (int i = 0; i < life; i++)
	{
		drawImg(0, i * 10, &love);//tools.h
	}


	// 修正推力
	if (push_x > 0)
	{
		push_x--;
		vx--;
	}
	if (push_x < 0)
	{
		push_x++;
		vx++;
	}
	if (push_y > 0)
	{
		push_y--;
		vy--;
	}
	if (push_y < 0)
	{
		push_y++;
		vy++;
	}
	// 推力为0时取消受击状态
	if (push_x == 0 && push_y == 0)
	{
		if (heated) initAnimation(Man_walk);
		heated = false;
	}
	// 判断播放动画的类型
	if (!heated)
	{
		if (stand && (vx != 0 || vy != 0))
		{
			stand = false;
			initAnimation(Man_walk);
		}
		if (abs(vx) < Utils::EQS && abs(vy) < Utils::EQS && stand == false)
		{
			vx = vy = 0;
			initAnimation(Man_Idle);
			stand = true;
		}
	}
}

void Player::onGroud(MonoObject* collider)
{
	if (!heated) nopush();
	collider->onCrash(this);
	if (collider->type == enemy)
	{
		if (body.posy + body.height - 2 < collider->body.posy)
		{
			//销毁敌人
			GameAudio(16);
			DestroyObject(collider);
			jump();

		}
	}
	if (collider->type == groud) canJump = true;
}

void Player::jump()
{
	if (push_y != 0) vy -= push_y;
	push_y = -300;
	vy += push_y;
	canJump = false;
}

void Player::nopush()
{
	if (push_x != 0) vx -= push_x;
	if (push_y != 0) vy -= push_y;
	push_x = 0;
	push_y = 0;
}


void Player::onCrash(MonoObject* collider)//判断一次
{
	if (collider->type == groud) nopush();
	if (collider->type == enemy)
	{
		if (body.posy + body.height - 2 < collider->body.posy)
		{
			//销毁敌人
			GameAudio(16);
			DestroyObject(collider);
			jump();

		}
		else if (!heated) // 阻止连续伤害
		{
			// 刷新原有的推力
			nopush();
			canJump = false;
			heated = true;
			initAnimation(DebuffMan_walk);
			// 根据敌人的坐标击退主角
			if (body.posx > collider->body.posx) push_x = 100;
			else push_x = -100;
			vx = push_x;
			if (body.posy > collider->body.posy) push_y = 100;
			else push_y = -100;
			vy = push_y;
			life--;
			GameAudio(18);
			if (life == 0)
			{
				GameAudio(25);
				//结束画面
			}
		}
	}
}
