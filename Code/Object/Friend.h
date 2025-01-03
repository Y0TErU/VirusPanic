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
	void Erace();				//削除
	void Draw() override;		//描画処理

	void PlayAnim();

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

	//状態変化時に必要なゲッターとセッター
	bool GetCanUpdate()
	{
		return canUpdate;
	}

	void SetCanUpdate(bool canUpdate_)
	{
		canUpdate = canUpdate_;
	}

private:
	const int createInterval{ 960 };	//生成の時間間隔
	const int changeStateInterval{ 660 };	//状態変化の時間間隔(11秒)
	int timeCount{ 0 };
	int height{ 96 };	//縦幅
	int width{ 96 };	//横幅
	bool canUpdate{ false };	//更新可能か
	bool beforeIsActive{ false };	//１つ前に生存しているかどうか

	int handle_tired{ -1 };
	int handle_animation[6]
	{
		-1,-1,-1,-1,-1,-1
	};

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

void InitializeFriends(Friend* friend_);			//初期化
void ChangeStateFriend(Friend* friend_);			//状態変化(疲れている)
void CrateFriends(Friend* friend_,int create_num_);	//生成
void UpdateFriends(Friend* friend_);				//更新
int SearchTiredFriend(Friend* friend_);				//疲れているオブジェクトを探す
//void EraseFriend(Friend* friend_);					//生存フラグが立っていないオブジェクトを消す

void PlayAnimation(Friend* friend_);