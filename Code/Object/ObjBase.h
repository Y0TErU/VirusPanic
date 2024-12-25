#pragma once

#include "../Collider/Collider.h"

#include <Dxlib.h>

class ObjBase
{
public:
	//メンバイニシャライザ
	ObjBase()
	{
		posX = 0;			//X座標
		posY = 0;			//Y座標
		width = 0;			//横幅
		height = 0;			//縦幅
		speed = 0.0f;		//速度
		isActive = false;	//生存フラグ	
		currentState = false;	//friendのみで使用(疲れている状況かどうか)
		handle_front = -1;	//正面の画像
		handle_left = -1;	//横の画像
		handle_right = -1;	//横の画像
		handle_back = -1;	//後ろの画像

		rect_collider =
		{
			posX,posY,
			width,height
		};
	}

	//オブジェクトの処理
	virtual void Initialize() = 0;	//初期化
	virtual void Draw() = 0;		//描画
	void Delete()					//描画の削除
	{
		DeleteGraph(handle_front);
		DeleteGraph(handle_right);
		DeleteGraph(handle_left);
		DeleteGraph(handle_back);
	}

	//ゲッター
	float GetPosX()
	{
		return posX;
	}
	float GetPosY()
	{
		return posY;
	}
	bool GetIsActive()
	{
		return isActive;
	}
	bool GetCurrentState()
	{
		return currentState;
	}

	RectCollider* GetCollider()
	{
		return &rect_collider;
	}

	//セッター
	void SetPosX(float pos_x_)
	{
		posX = pos_x_;
	}
	void SetPosY(float pos_y_)
	{
		posX = pos_y_;
	}
	void SetIsActive(bool isActive_)
	{
		isActive = isActive_;
	}

protected:
	int posX;			//X座標
	int posY;			//Y座標
	int width;
	int height;
	float speed;		//速度
	bool isActive;		//生存フラグ
	bool currentState;	//疲れているかどうか （falseは元気状態、trueは疲れている）

	RectCollider rect_collider;	//当たり判定用	

	//描画ハンドル
	int handle_front;	//正面の画像
	int handle_right;	//右向きの画像
	int handle_left;	//左向きの画像
	int handle_back;	//後ろの画像
	
};