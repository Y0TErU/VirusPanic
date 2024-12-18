#pragma once

//矩形の判定
struct RectCollider
{
	int posX;	//X座標
	int posY;	//Y座標
	int width;	//横幅
	int height;	//縦幅
};

//円の判定
struct CircleCollider
{
	int posX;	//X座標
	int posY;	//Y座標
	int radius;
};

//矩形と矩形の当たり判定用関数
bool OnCollisionRectToRect(RectCollider collider_01_, RectCollider collider_02_);
//円と円の当たり判定用関数
bool OnCollisionCircleToCircle(CircleCollider collider_01_, CircleCollider collider_02_);
//点と矩形の当たり判定用関数
bool OnCollisionPointToRect(RectCollider collider_rect_, int point_x, int point_y_);

