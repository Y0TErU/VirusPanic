#pragma once

#include "ObjBase.h"

class Player : public ObjBase
{
public:
	void LoadTexture();		//描画の読み込み
	void Initialize();		//初期化
	void Update();		//更新処理
	void Draw() override;	//描画処理

	//ui関係の関数
	void LoadUiTexture();	//SPACE_KEYのUI
	void DrawSpaceKey();	
	void DeleteSpaceKey();

	//白血球との判定用
	void ToFriend(bool isActive_, bool isTouch_, RectCollider* friend_top_, RectCollider* friend_botom_, RectCollider* friend_left_, RectCollider* friend_right_);
	bool TouchFriend(bool isActive_, bool tired_);

private:
	int nextPosX{ posX };
	int nextPosY{ posY };
	float vecX{ 0.0f };		//移動用ベクトル
	float vecY{ 0.0f };
	int height{ 60 };		//縦幅
	int width{ 75 };
	bool canTouch{ false };	//白血球にタッチ可能かどうか

	//UI SPACEキー
	int handle_space{ -1 };	//UIハンドル(SPACE)
};