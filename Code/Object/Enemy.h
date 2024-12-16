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
	void LoadTexture();				//描画の読み込み
	void Update(ObjBase* target_);	//更新処理
	void Draw() override;			//描画処理

private:
	float nextPosX{ posX };
	float nextPosY{ posY };
	float vecX{ 0.0f };		//移動方向ベクトル
	float vecY{ 0.0f };
	float height{ 75 };	//縦幅
	float width{ 90 };	//横幅
	float enemyCounter{ 0 };
	
	RectCollider enemyCollider
	{
		posX,posY,
		width,height
	};

	ObjBase* target{ nullptr };	//追跡先

};

void InitializeEnemies(Enemy* enemy_[EnemyMaxNum]);
void CreateEnemies(Enemy* enemy_[EnemyMaxNum], int pos_x_, int pos_y_);

