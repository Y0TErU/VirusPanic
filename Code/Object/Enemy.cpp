#include <Dxlib.h>
#include <math.h>

#include "Enemy.h"
#include "Stage.h"

Stage enemyToStage;

void Enemy::Initialize()
{
	posX = 148;
	posY = 600;
	speed = 5.2;
	isActive = false;
	height = 75;
	width = 90;
	enemyCounter = 0;
	rect_collider =
	{
		posX,posY,
		width,height
	};

	handle_front = -1;
	handle_right = -1;
	handle_left = -1;
	handle_back = -1;
}

void Enemy::Create(int pos_x_, int pos_y_)
{
	posX = pos_x_;
	posY = pos_y_;
	isActive = true;
}

void Enemy::LoadTexture()
{
	if (handle_front == -1)
	{
		handle_front = LoadGraph("Res/Object/virus_front.png");
	}
	if (handle_right == -1)
	{
		handle_right = LoadGraph("Res/Object/virus_right.png");
	}
	if (handle_left == -1)
	{
		handle_left = LoadGraph("Res/Object/virus_left.png");
	}
	if (handle_back == -1)
	{
		handle_back = LoadGraph("Res/Object/virus_back.png");
	}
	
}

void Enemy::Update(ObjBase* target_)
{
	target = target_;	//追跡対象のアドレス

	if (isActive == true)
	{
		nextPosX = posX;
		nextPosY = posY;

		vecX = 0.0f;
		vecY = 0.0f;

		vecX = target->GetPosX() - posX;
		vecY = target->GetPosY() - posY;

		float length = sqrtf(vecX * vecX + vecY * vecY);

		nextPosX += vecX / length * speed;
		nextPosY += vecY / length * speed;

 		float side = 0.0f;
		rect_collider.posX = nextPosX;

		if (enemyToStage.OnCollisionStageAndRect(rect_collider, vecX, 0.0f, &side, nullptr) == false)
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
		if (enemyToStage.OnCollisionStageAndRect(rect_collider, 0.0f, vecY, nullptr, &side) == false)
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
			posX = nextPosX;
			rect_collider.posY = posY;
			
		}
	}
}

void Enemy::ToPlayer(ObjBase* player_)
{
	if (OnCollisionRectToRect(rect_collider,*player_->GetCollider()) == true)
	{
		player_->SetIsActive(false);
	}
}

void Enemy::ToFriend(bool isTouch_, RectCollider* friend_top_, RectCollider* friend_botom_, RectCollider* friend_left_, RectCollider* friend_right_)
{
	if (isTouch_ == true)
	{
		//上1マスの判定
		if (OnCollisionRectToRect(rect_collider, *friend_top_) == true || OnCollisionRectToRect(rect_collider, *friend_botom_) == true ||
			OnCollisionRectToRect(rect_collider, *friend_left_) == true || OnCollisionRectToRect(rect_collider, *friend_right_) == true)	//当たっている
		{
			canTouch = true;	//タッチ
		}
		else
		{
			canTouch = false;	//タッチしていない
		}
	}
}

bool Enemy::TouchFriend(bool isActive_)
{
	if (isActive_ == true)
	{
		if (canTouch == true)
		{
			return true;
		}
		return false;
	}
	return false;
	}

void Enemy::Draw()
{
	if (isActive == true)
	{
		if (vecY > 0.0f)	//下向きに移動中
		{
			DrawExtendGraph((int)posX, (int)posY, (int)posX + (int)width, (int)posY + (int)height, handle_front, true);	//正面を向いている
		}
		else if (vecY < 0.0f)	//上向きに移動中
		{
			DrawExtendGraph((int)posX, (int)posY, (int)posX + (int)width, (int)posY + (int)height, handle_back, true);	//後ろを向いている
		}
		else if (vecX > 0.0f)	//右向きに移動中
		{
			DrawExtendGraph((int)posX, (int)posY, (int)posX + (int)width, (int)posY + (int)height, handle_right, true);	//右を向いている
		}
		else if (vecX < 0.0f)	//左向きに移動中
		{
			DrawExtendGraph((int)posX, (int)posY, (int)posX + (int)width, (int)posY + (int)height, handle_left, true);	//左を向いている
		}
	}
}


void InitializeEnemies(Enemy* enemy_[EnemyMaxNum])
{
	for (int i = 0; i < EnemyMaxNum; i++)
	{
		if (enemy_[i]->GetIsActive() == true)
		{
			enemy_[i]->Initialize();
		}
	}
}

void CreateEnemies(Enemy* enemy_[EnemyMaxNum], int pos_x_, int pos_y_)
{
	for (int i = 0; i < EnemyMaxNum; i++)
	{
		if (enemy_[i]->GetIsActive() == false)
		{
			enemy_[i]->Create(pos_x_,pos_y_);
		}

		break;
	}

}
