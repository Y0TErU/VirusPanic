#include <Dxlib.h>
#include <math.h>

#include "Player.h"
#include "Stage.h"

Stage playerToStage;

void Player::Initialize()
{
	posX = 148;
	posY = 200;
	speed = 4.0f;
	isActive = true;
	rect_collider =
	{
		posX,posY,
		width,height
	};
}

void Player::LoadTexture()
{
	if (handle_front == -1)
	{
		handle_front = LoadGraph("Res/Object/vaccine_front.png");
	}
	if (handle_left == -1)
	{
		handle_left = LoadGraph("Res/Object/vaccine_left.png");
	}
	if (handle_right == -1)
	{
		handle_right = LoadGraph("Res/Object/vaccine_right.png");
	}
	if (handle_back == -1)
	{
		handle_back = LoadGraph("Res/Object/vaccine_back.png");
	}
}

void Player::Update()
{
	if (isActive == true)
	{
		nextPosX = posX;
		nextPosY = posY;

		vecX = 0.0f;
		vecY = 0.0f;

		if (CheckHitKey(KEY_INPUT_A))
		{
			vecX -= speed;
		}

		else if (CheckHitKey(KEY_INPUT_D))
		{
			vecX += speed;
		}

		else if (CheckHitKey(KEY_INPUT_W))
		{
			vecY -= speed;
		}

		else if (CheckHitKey(KEY_INPUT_S))
		{
			vecY += speed;
		}

		nextPosX += vecX;
		nextPosY += vecY;

		float side = 0.0f;
		rect_collider.posX = nextPosX;

		if (playerToStage.OnCollisionStageAndRect(rect_collider, vecX, 0.0f, &side, nullptr) == false)
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

			rect_collider.posX = posX;
		}

		rect_collider.posY = nextPosY;
		if (playerToStage.OnCollisionStageAndRect(rect_collider, 0.0f, vecY, nullptr, &side) == false)
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
			rect_collider.posY = posY;
		}
	}
	
}

void Player::Draw()
{
	if (isActive == true)
	{
		if (vecX == 0.0f && vecY == 0.0f)	//Ã~ó‘Ô
		{
			DrawExtendGraph(posX, posY - 65,posX + 75, posY - 65 + 125 , handle_front, true);	//³–Ê‚ğŒü‚¢‚Ä‚¢‚é
		}
		else if (vecY > 0.0f)	//‰ºŒü‚«‚ÉˆÚ“®’†
		{
			DrawExtendGraph(posX, posY - 65, posX + 75, posY - 65 + 125, handle_front, true);	//³–Ê‚ğŒü‚¢‚Ä‚¢‚é
		}
		else if (vecY < 0.0f)	//ãŒü‚«‚ÉˆÚ“®’†
		{
			DrawExtendGraph(posX, posY - 65, posX + 75, posY - 65 + 125, handle_back, true);	//Œã‚ë‚ğŒü‚¢‚Ä‚¢‚é
		}
		else if (vecX > 0.0f)	//‰EŒü‚«‚ÉˆÚ“®’†
		{
			DrawExtendGraph(posX, posY - 65, posX + 75, posY - 65 + 125, handle_right, true);	//‰E‚ğŒü‚¢‚Ä‚¢‚é
		}
		else if (vecX < 0.0f)	//¶Œü‚«‚ÉˆÚ“®’†
		{
			DrawExtendGraph(posX, posY - 65, posX + 75, posY - 65 + 125, handle_left, true);	//¶‚ğŒü‚¢‚Ä‚¢‚é
		}
	}
}
