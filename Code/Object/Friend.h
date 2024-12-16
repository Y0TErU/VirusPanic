#pragma once

#include "ObjBase.h"
#include "../Collider/Collider.h"

const int FriendMaxNum{ 15 };
const int initialFriendNum{ 5 };

class Friend : public ObjBase
{
public:
	void Initialize() override;	//初期化
	void Create();				//生成
	void LoadTexture();			//描画の読み込み
	void Update();				//更新処理
	void Draw() override;		//描画処理

	//ステータスのゲッター
	bool GetCurrentState()
	{
		return currentState;
	}


private:
	const int createInterval{ 960 };	//生成の時間間隔
	const int changeStateInterval{ 300 };	//状態変化の時間間隔
	bool currentState{ false };	//現在のステータス(false は元気状態)
	
	int timeCount{ 0 };
	float height{ 96 };	//縦幅
	float width{ 96 };	//横幅

	RectCollider enemyCollider
	{
		posX,posY,
		width,height
	};
};

//void InitializeFriend(ObjBase* friend_[FriendMaxNum]);

void CreateFriends(Friend* friend_[FriendMaxNum]);


