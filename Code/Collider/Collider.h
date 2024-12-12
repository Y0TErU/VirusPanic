#pragma once

//矩形の判定
struct RectCollider
{
	float posX;		//X座標
	float posY;		//Y座標
	float width;	//横幅
	float height;	//縦幅
};

//円の判定
struct CircleCollider
{
	float posX;		//X座標
	float posY;		//Y座標
	float radius;
};

//矩形と矩形の当たり判定用関数
bool OnCollisionRectToRect(RectCollider collider_01_, RectCollider collider_02_);
//円と円の当たり判定用関数
bool OnCollisionCircleToCircle(CircleCollider collider_01_, CircleCollider collider_02_);
//点と矩形の当たり判定用関数
bool OnCollisionPointToRect(RectCollider collider_rect_, int point_x, int point_y_);

/*
//ステージとの当たり判定
bool OnCollisionStageToRect(int stage_[mapHeight][mapwidth],
	int min_x_, int max_x_, int min_y_, int max_y_, float vec_x_, float vec_y_, float* side_x_, float* side_y_);
//ステージのどの辺に当たるかを判定
bool OnCollisionStageAndRect(int stage_[mapHeight][mapwidth],
	RectCollider rect_, float vec_x_, float vec_y_, float* side_x_, float* side_y_);

*/
