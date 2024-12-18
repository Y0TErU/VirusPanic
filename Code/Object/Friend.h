#pragma once

#include "ObjBase.h"

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

	//RectColliderのゲッター
	RectCollider* GetTopCollider()
	{
		return &top_collider;	//1マス上の座標
	}
	RectCollider* GetBotomCollider()
	{
		return &botom_collider;	//1マス下の座標
	}
	RectCollider* GetRightCollider()
	{
		return &left_collider;	//1マス左の座標
	}
	RectCollider* GetLeftCollider()
	{
		return &right_collider;	//1マス右の座標
	}

private:
	const int createInterval{ 960 };	//生成の時間間隔
	const int changeStateInterval{ 300 };	//状態変化の時間間隔
	bool currentState{ false };	//現在のステータス(false は元気状態)
	
	int timeCount{ 0 };
	int height{ 96 };	//縦幅
	int width{ 96 };	//横幅

	RectCollider top_collider
	{
		posX,posY - height,
		width,height - height
	};
	RectCollider botom_collider
	{
		posX,posY + height,
		width,height + height
	};
	RectCollider left_collider
	{
		posX - width,posY,
		width - width,height
	};
	RectCollider right_collider
	{
		posX + width,posY,
		width + width,height
	};
};

void ChangeStateFriend(Friend* friend_);


