#include <Dxlib.h>
#include <math.h>

#include "Enemy.h"
#include "Stage.h"

Stage enemyToStage;

/*
Enemy::Enemy()
{
	posX = 148;
	posY = 600;
	nextPosX = 0;
	nextPosY = 0;
	speed = 5.2;
	isActive = false;
	handle = -1;
	vecX = 0.0f;
	vecY = 0.0f;
	height = 75;
	width = 90;
	enemyCollider =
	{
		posX,posY,
		width,height
	};

}

*/

void Enemy::Initialize()
{
	posX = 148;
	posY = 600;
	speed = 5.2;
	isActive = false;
	height = 75;
	width = 90;
	enemyCollider =
	{
		posX,posY,
		width,height
	};
}

void Enemy::Create(int pos_x_, int pos_y_)
{
	posX = pos_x_;
	posY = pos_y_;
	isActive = true;
}

void Enemy::LoadTexture()
{
	if (handle == -1)
	{
		handle = LoadGraph("Res/Object/Virus.png");
	}
}

void Enemy::Update(ObjBase* target_)
{
	target = target_;
	for (int i = 0; i < EnemyMaxNum; i++)
	{

	}
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
		enemyCollider.posX = nextPosX;
		

		if (enemyToStage.OnCollisionStageAndRect(enemyCollider, vecX, 0.0f, &side, nullptr) == false)
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
			posY = nextPosY;
			enemyCollider.posX = posX;
		}

		enemyCollider.posY = nextPosY;
		if (enemyToStage.OnCollisionStageAndRect(enemyCollider, 0.0f, vecY, nullptr, &side) == false)
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
			enemyCollider.posY = posY;
			
		}
		
	}
}

void Enemy::Draw()
{
	if (isActive)
	{
		DrawGraph((int)posX, (int)posY, handle, true);
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
