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
		speed = 0.0f;		//速度
		isActive = false;	//生存フラグ
		handle = -1;		//描画ハンドル
	}

	//オブジェクトの処理
	virtual void Initialize() = 0;	//初期化
	virtual void Draw() = 0;		//描画
	void Delete()					//描画の削除
	{
		DeleteGraph(handle);
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
	int GetHandle()
	{
		return handle;
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
	float posX;			//X座標
	float posY;			//Y座標
	float speed;		//速度
	bool isActive;		//生存フラグ
	int handle;			//描画ハンドル
	
};