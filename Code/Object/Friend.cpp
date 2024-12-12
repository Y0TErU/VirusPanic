#include <Dxlib.h>
#include <math.h>

#include "Friend.h"
#include "Stage.h"

void Friend::Initialize()
{
	isActive = false;
	height = 96;
	width = 96;

}

void Friend::Create(int pos_x_,int pos_y_)
{
	posX = pos_x_;
	posY = pos_y_;
	isActive = true;
}

void Friend::Update()
{
	
}

void Friend::LoadTexture()
{
	if (handle == -1)
	{
		handle = LoadGraph("Res/Object/WhiteBloodCell.png");
	}
}

void Friend::Draw()
{
	if (isActive)
	{
		DrawGraph((int)posX, (int)posY, handle, true);
	}
}

void InitializeFriend(Friend* friend_[FriendMaxNum])
{
	for (int i = 0; i < FriendMaxNum; i++)
	{
		if (friend_[i]->GetIsActive() == true)
		{
			friend_[i]->Initialize();
		}
	}

}

void CreateFriend(Friend* friend_[FriendMaxNum])
{
	for (int i = 0; i < FriendMaxNum; i++)
	{
		if (friend_[i]->GetIsActive() == false)
		{
			friend_[i]->Create();
		}
		break;
	}

}

