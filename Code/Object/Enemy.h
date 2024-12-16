#pragma once

#include "ObjBase.h"
#include "../Collider/Collider.h"

const int EnemyMaxNum{ 5 };

class Enemy : public ObjBase
{
public:
	//Enemy();
	void Initialize();
	void Create(int pos_x_, int pos_y_);
	void LoadTexture();				//�`��̓ǂݍ���
	void Update(ObjBase* target_);	//�X�V����
	void Draw() override;			//�`�揈��

private:
	float nextPosX{ posX };
	float nextPosY{ posY };
	float vecX{ 0.0f };		//�ړ������x�N�g��
	float vecY{ 0.0f };
	float height{ 75 };	//�c��
	float width{ 90 };	//����
	float enemyCounter{ 0 };
	
	RectCollider enemyCollider
	{
		posX,posY,
		width,height
	};

	ObjBase* target{ nullptr };	//�ǐՐ�

};

void InitializeEnemies(Enemy* enemy_[EnemyMaxNum]);
void CreateEnemies(Enemy* enemy_[EnemyMaxNum], int pos_x_, int pos_y_);

