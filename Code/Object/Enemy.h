#pragma once

#include "ObjBase.h"

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

	void ToPlayer(ObjBase* player_);
	void ToFriend(ObjBase* friend_);

private:
	int nextPosX{ posX };
	int nextPosY{ posY };
	float vecX{ 0.0f };		//�ړ������x�N�g��
	float vecY{ 0.0f };
	float enemyCounter{ 0 };
	
	ObjBase* target{ nullptr };	//�ǐՐ�

};

void InitializeEnemies(Enemy* enemy_[EnemyMaxNum]);
void CreateEnemies(Enemy* enemy_[EnemyMaxNum], int pos_x_, int pos_y_);

