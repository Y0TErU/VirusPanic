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
	rect_collider = 
	{
		posX, posY,
		width, height
	};
	handle_front = -1;
}

void Friend::Create()
{
	if (isActive == false)
	{
		FriendToStage.GetRandomStage();
		posX = static_cast<int>(FriendToStage.GetStagePosX());
		posY = static_cast<int>(FriendToStage.GetStagePosY());
		isActive = true;

		top_collider =
		{
			posX,posY - height,
			width,height
		};
		botom_collider =
		{
			posX,posY + height,
			width,height
		};
		left_collider =
		{
			posX - width,posY,
			width,height
		};
		right_collider =
		{
			posX + width,posY,
			width,height
		};
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
	if (handle_front == -1)
	{
		handle_front = LoadGraph("Res/Object/WhiteBloodCell.png");
	}
}

void Friend::Draw()
{
	if (isActive == true)
	{
		if (currentState == false)
		{
			DrawExtendGraph(static_cast<int>(posX), static_cast<int>(posY), static_cast<int>(posX + width), static_cast<int>(posY + height), handle_front, true);
		}
		else
		{
			DrawExtendGraph(static_cast<int>(posX), static_cast<int>(posY), static_cast<int>(posX + width) +10, static_cast<int>(posY + height) + 10, handle_front, true);

		}
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
void CreateFriends(Friend* friend_[FriendMaxNum])
{
	for (int i = 0; i < FriendMaxNum; i++)
	{
		friend_[i]->Create();
	}
}
*/

void ChangeStateFriend(Friend* friend_)
{
	static int count = 0;	

	for (int i = 0; i < FriendMaxNum; i++)
	{
		if (friend_[i].GetIsActive() == true)
		{
			if (friend_[i].GetCurrentState() == false)
			{
				if (friend_[i - 1].GetCurrentState() == true)
				{
					break;
				}

				friend_[i].Update();

			}
		break;
		}
		
	}
}



