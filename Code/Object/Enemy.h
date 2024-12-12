#pragma once

#include "ObjBase.h"
#include "../Collider/Collider.h"

class Enemy : public ObjBase
{
public:
	Enemy();
	void Initialize();
	void LoadTexture();				//�`��̓ǂݍ���
	void Update(ObjBase* target_);	//�X�V����
	void Draw() override;			//�`�揈��

private:
	const int EnemyMaxNum{ 5 };
	float nextPosX{ posX };
	float nextPosY{ posY };
	float vecX{ 0.0f };		//�ړ������x�N�g��
	float vecY{ 0.0f };
	float height{ 75 };	//�c��
	float width{ 90 };	//����
	
	RectCollider enemyCollider
	{
		posX,posY,
		width,height
	};

	ObjBase* target{ nullptr };	//�ǐՐ�

};

void InitializeEnemies(Enemy* enemy_);
void CreateEnemies(Enemy* enemy_, int pos_x_, int pos_y_);



