#pragma once

#include "ObjBase.h"

const int EnemyMaxNum{ 5 };

class Enemy : public ObjBase
{
public:
	//Enemy();
	void Initialize();
	void Create(int pos_x_, int pos_y_);
	void LoadTexture();				//描画の読み込み
	void Update(ObjBase* target_);	//更新処理
	void Draw() override;			//描画処理

	void ToPlayer(ObjBase* player_);
	void ToFriend(ObjBase* friend_);

private:
	int nextPosX{ posX };
	int nextPosY{ posY };
	float vecX{ 0.0f };		//移動方向ベクトル
	float vecY{ 0.0f };
	float enemyCounter{ 0 };
	
	ObjBase* target{ nullptr };	//追跡先

};

void InitializeEnemies(Enemy* enemy_[EnemyMaxNum]);
void CreateEnemies(Enemy* enemy_[EnemyMaxNum], int pos_x_, int pos_y_);

