#pragma once

#include "ObjBase.h"
#include "../Collider/Collider.h"

Stage playerToStage;

class Player : public ObjBase
{
public:
	void LoadTexture();		//描画の読み込み
	void Initialize();		//初期化
	void Update();	//更新処理
	void Draw() override;	//描画処理

private:
	float nextPosX{ posX };
	float nextPosY{ posY };
	float vecX{ 0.0f };		//移動用ベクトル
	float vecY{ 0.0f };
	float height{ 50 };	//縦幅
	float width{ 75 };

	RectCollider playerCollider		//当たり判定用
	{
		posX,posY,
		width,height
	};
};