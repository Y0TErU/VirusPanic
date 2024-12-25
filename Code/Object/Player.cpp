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
	currentState = true;
	rect_collider =
	{
		posX,posY,
		width,height
	};
	canTouch = false;
	//�e�N�X�`���n���h��
	handle_front = -1;
	handle_left = -1;
	handle_right = -1;
	handle_back = -1;
	//UI�n���h��
	handle_space = -1;
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

void Player::LoadUiTexture()
{
	if (handle_space == -1)
	{
		handle_space = LoadGraph("Res/Ui/Ui_space.png");
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

void Player::ToFriend(bool isActive_,bool isTouch_, RectCollider *friend_top_, RectCollider *friend_botom_, RectCollider *friend_left_, RectCollider *friend_right_)
{
	if (isTouch_ == true && isActive_ == true)
	{
		//��1�}�X�̔���
		if (OnCollisionRectToRect(rect_collider, *friend_top_) == true || OnCollisionRectToRect(rect_collider, *friend_botom_) == true ||
			OnCollisionRectToRect(rect_collider, *friend_left_) == true || OnCollisionRectToRect(rect_collider, *friend_right_) == true)	//�������Ă���
		{
			canTouch = true;	//�^�b�`�\
		}
		else
		{
			canTouch = false;	//�^�b�`�s��
		}
	}
}

bool Player::TouchFriend(bool isActive_,bool tired_)
{
	if (isActive_ == true && tired_ == true)
	{
		if (canTouch == true && CheckHitKey(KEY_INPUT_SPACE))
		{
			canTouch = false;
			return true;
		}
		return false;
	}
	return false;
}


void Player::Draw()
{
	if (isActive == true)
	{
		if (vecX == 0.0f && vecY == 0.0f)	//�Î~���
		{
			DrawExtendGraph(posX, posY - 65,posX + 75, posY - 65 + 125 , handle_front, true);	//���ʂ������Ă���
		}
		else if (vecY > 0.0f)	//�������Ɉړ���
		{
			DrawExtendGraph(posX, posY - 65, posX + 75, posY - 65 + 125, handle_front, true);	//���ʂ������Ă���
		}
		else if (vecY < 0.0f)	//������Ɉړ���
		{
			DrawExtendGraph(posX, posY - 65, posX + 75, posY - 65 + 125, handle_back, true);	//���������Ă���
		}
		else if (vecX > 0.0f)	//�E�����Ɉړ���
		{
			DrawExtendGraph(posX, posY - 65, posX + 75, posY - 65 + 125, handle_right, true);	//�E�������Ă���
		}
		else if (vecX < 0.0f)	//�������Ɉړ���
		{
			DrawExtendGraph(posX, posY - 65, posX + 75, posY - 65 + 125, handle_left, true);	//���������Ă���
		}
	}
}

void Player::DrawSpaceKey()
{
	if (canTouch == true)
	{
		DrawGraph(posX, posY, handle_space, true);
	}
}

void Player::DeleteSpaceKey()
{
	DeleteGraph(handle_space);
}