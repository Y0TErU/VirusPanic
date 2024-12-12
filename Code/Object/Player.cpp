#include <Dxlib.h>
#include <math.h>

#include "Player.h"
#include "Stage.h"

Stage playerToStage;

void Player::Initialize()
{
	posX = 148;
	posY = 200;
	nextPosX = 0;
	nextPosY = 0;
	speed = 4.0f;
	isActive = true;
	handle = -1;
	vecX = 0;
	vecY = 0;
	height = 75;
	width = 90;
	playerCollider =
	{
		posX,posY,
		width,height
	};
}

void Player::LoadTexture()
{
	if (handle == -1)
	{
		handle = LoadGraph("Res/Object/Vaccine.png");
	}
}

void Player::Update()
{
	nextPosX = posX;
	nextPosY = posY;

	vecX = 0.0f;
	vecY = 0.0f;

	if (CheckHitKey(KEY_INPUT_A))
	{
		vecX -= speed;
	}

	if (CheckHitKey(KEY_INPUT_D))
	{
		vecX += speed;
	}

	if (CheckHitKey(KEY_INPUT_W))
	{
		vecY -= speed;
	}

	if (CheckHitKey(KEY_INPUT_S))
	{
		vecY += speed;
	}

	nextPosX += vecX;
	nextPosY += vecY;

	float side = 0.0f;
	playerCollider.posX = nextPosX;

	if (playerToStage.OnCollisionStageAndRect(playerCollider, vecX, 0.0f, &side, nullptr) == false)
	{
		posX = nextPosX;
	}
	else
	{
		if (vecX > 0.0f)
		{
			posX = (side - width) - 1.0f;
		}
		else if (vecX < 0.0f)
		{
			posX = side + 1.0f;
		}

		playerCollider.posX = posX;
	}
	
	playerCollider.posY = nextPosY;
	if(playerToStage.OnCollisionStageAndRect(playerCollider, 0.0f, vecY, nullptr , &side) == false)
	{
		posY = nextPosY;
	}
	else
	{
		if (vecY > 0.0f)
		{
			posY = (side - height) - 1.0f;
		}
		else if (vecY < 0.0f)
		{
			posY = side + 1.0f;
		}
		playerCollider.posY = posY;
	}
}

void Player::Draw()
{
	DrawGraph((int)posX, (int)posY - 75, handle, true);
}
