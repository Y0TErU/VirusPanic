#include <Dxlib.h>
#include <math.h>

#include "Friend.h"
#include "Stage.h"

Stage FriendToStage;

void Friend::Initialize()
{
	isActive = false;
	height = 96;
	width = 96;
	currentState = fine;
	friendCounter = 0;
	timeCount = 0;
}

void Friend::Create()
{
	FriendToStage.GetRandomStage();
	posX = FriendToStage.GetStagePosX();
	posY = FriendToStage.GetStagePosY();
	isActive = true;
}

void Friend::Update()
{
	timeCount++;
	if (timeCount >= changeStateInterval)
	{
		if (currentState == fine)
		{
			currentState = tired;
		}
	}
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

