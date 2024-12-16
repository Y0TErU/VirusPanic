#include <Dxlib.h>
#include <math.h>

#include "Friend.h"
#include "Stage.h"

Stage FriendToStage;

void Friend::Initialize()
{
	posX = 0;
	posY = 0;
	isActive = false;
	height = 96;
	width = 96;
	currentState = false;
	timeCount = 0;
}

void Friend::Create()
{
	if (isActive == false)
	{
		FriendToStage.GetRandomStage();
		posX = (float)FriendToStage.GetStagePosX();
		posY = (float)FriendToStage.GetStagePosY();
		isActive = true;
	}
	
	
}

void Friend::Update()
{
	timeCount++;
	if (isActive == true)
	{
		if (timeCount >= changeStateInterval)
		{
			if (currentState == false)
			{
				currentState = true;
			}
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
	if (isActive = true)
	{
		DrawGraph((int)posX, (int)posY, handle, true);
	}
}

/*
void InitializeFriend(ObjBase* friend_)
{
	if (friend_->GetIsActive() == true)
	{
		friend_->Initialize();
	}
}
*/

void CreateFriends(Friend* friend_[FriendMaxNum])
{
	for (int i = 0; i < FriendMaxNum; i++)
	{
		friend_[i]->Create();
	}
}



