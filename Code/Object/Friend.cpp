#include <Dxlib.h>
#include <math.h>

#include "Friend.h"
#include "Stage.h"

Stage FriendToStage;

Friend::Friend()
{
	posX = 0;
	posY = 0;
	speed = 0;
	isActive = false;
	handle = -1;
	friendCounter = 0;
	height = 96;	//ècïù
	width = 96;	//â°ïù

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

