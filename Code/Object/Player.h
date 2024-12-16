#pragma once

#include "ObjBase.h"

class Player : public ObjBase
{
public:
	void LoadTexture();		//描画の読み込み
	void Initialize();		//初期化
	void Update();	//更新処理
	void Draw() override;	//描画処理


private:
	int nextPosX{ posX };
	int nextPosY{ posY };
	float vecX{ 0.0f };		//移動用ベクトル
	float vecY{ 0.0f };
	int height{ 60 };		//縦幅
	int width{ 75 };

	
};