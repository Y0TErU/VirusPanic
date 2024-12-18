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
	void ToFriend(bool isTouch_, RectCollider* friend_top_, RectCollider* friend_botom_, RectCollider* friend_left_, RectCollider* friend_right_);
	bool TouchFriend(bool isActive_);

private:
	int nextPosX{ posX };
	int nextPosY{ posY };
	float vecX{ 0.0f };		//移動方向ベクトル
	float vecY{ 0.0f };
	float enemyCounter{ 0 };
	bool canTouch{ false };
	
	ObjBase* target{ nullptr };	//追跡先

};

void InitializeEnemies(Enemy* enemy_[EnemyMaxNum]);
void CreateEnemies(Enemy* enemy_[EnemyMaxNum], int pos_x_, int pos_y_);

