#include <Dxlib.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Friend.h"
#include "Stage.h"

Stage FriendToStage;

void Friend::Initialize()
{
	posX = 0;
	posY = 0;
	isActive = false;
	beforeIsActive = false;
	height = 96;
	width = 96;
	currentState = false;
	timeCount = 0;
	canUpdate = false;
	beforeIsActive = false;

	handle_front = -1;
	handle_tired = -1;
}

void Friend::Create()
{
	FriendToStage.GetRandomStage();
	posX = static_cast<int>(FriendToStage.GetStagePosX());
	posY = static_cast<int>(FriendToStage.GetStagePosY());
	isActive = true;
	beforeIsActive = true;
	currentState = false;

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

void Friend::Update()
{
	if (isActive == true && canUpdate == true)
	{
		timeCount++;
		if (timeCount >= changeStateInterval)
		{
			currentState = true;
			timeCount = 0;
		}
	}
}

void Friend::Erace()
{
	if (isActive == false && beforeIsActive == true)
	{
		posX = 0;
		posY = 0;
		isActive = false;
		beforeIsActive = false;
		height = 96;
		width = 96;
		currentState = false;
		timeCount = 0;
		canUpdate = false;
	}
}

void Friend::LoadTexture()
{
	handle_front = LoadGraph("Res/Object/WhiteBloodCell.png");
	handle_tired = LoadGraph("Res/Object/WhiteBloodCell_tired.png");
	
	handle_animation[0] = LoadGraph("Res/Animation/smoke1.png");
	handle_animation[1] = LoadGraph("Res/Animation/smoke2.png");
	handle_animation[2] = LoadGraph("Res/Animation/smoke3.png");
	handle_animation[3] = LoadGraph("Res/Animation/smoke4.png");
	handle_animation[4] = LoadGraph("Res/Animation/smoke5.png");
	handle_animation[5] = LoadGraph("Res/Animation/smoke6.png");
	
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
			DrawExtendGraph(static_cast<int>(posX), static_cast<int>(posY), static_cast<int>(posX + width), static_cast<int>(posY + height), handle_tired, true);
		}
	}
}

void Friend::PlayAnim()
{
	if (beforeIsActive == true && isActive == false)
	{
		for (int i = 0; i < 6; i++)
		{
			DrawExtendGraph(static_cast<int>(posX), static_cast<int>(posY), static_cast<int>(posX + width), static_cast<int>(posY + height), handle_animation[i], true);
		}
	}
}

void ChangeStateFriend(Friend* friend_)
{
	int friendCounter = 0;
	for (int i = 0; i < FriendMaxNum; i++)
	{
		if (friend_[i].GetCanUpdate() == true)
		{
			return;	//ó‘Ô•Ï‰»‚ª‰Â”\‚È”’ŒŒ‹…‚ª‚¢‚é‚È‚çI—¹
		}
	}

	srand((unsigned int)time(NULL));

	while (true)
	{
		int make = rand() % FriendMaxNum;
		if (friend_[make].GetIsActive() == true && friend_[make].GetCanUpdate() == false)
		{
			friend_[make].SetCanUpdate(true);
			break;
		}
	}
}

void InitializeFriends(Friend* friend_)
{
	for (int i = 0; i < FriendMaxNum; i++)
	{
		friend_[i].Initialize();
	}
}

void UpdateFriends(Friend* friend_)
{
	for (int i = 0; i < FriendMaxNum; i++)
	{
		friend_[i].Update();
	}
}

void CrateFriends(Friend* friend_,int create_num_)
{
	int createCounter = 0;
	int i = 0;
	while (createCounter < create_num_)
	{
		if (friend_[i].GetIsActive() == false)
		{
			friend_[i].Create();
			i++;
			createCounter++;
		}
		else
		{
			i++;
		}
	}
}

void EraseFriend(Friend* friend_)
{
	for (int i = 0; i < FriendMaxNum; i++)
	{
		if (friend_[i].GetIsActive() == false)
		{
			friend_[i].Erace();
		}
	}
}

int SearchTiredFriend(Friend* friend_)
{
	for (int i = 0; i < FriendMaxNum; i++)
	{
		if (friend_[i].GetCurrentState() == true && friend_[i].GetIsActive() == true)
		{
			return i;
		}
	}
}

void PlayAnimation(Friend* friend_)
{
	for (int i = 0; i < FriendMaxNum; i++)
	{
		friend_[i].PlayAnim();
	}
}