#include <Dxlib.h>
#include <math.h>

#include "Collider.h"

//矩形と矩形の当たり判定用関数
bool OnCollisionRectToRect(RectCollider collider_01_, RectCollider collider_02_)
{
	float rect01_min_x = collider_01_.posX;							//矩形01の左辺
	float rect01_max_x = collider_01_.posX + collider_01_.width;	//矩形01の右辺
	float rect01_min_y = collider_01_.posY;							//矩形01の上辺
	float rect01_max_y = collider_01_.posY + collider_01_.height;	//矩形01の下辺

	float rect02_min_x = collider_02_.posX;							//矩形02の左辺
	float rect02_max_x = collider_02_.posX + collider_02_.width;	//矩形02の右辺
	float rect02_min_y = collider_02_.posY;							//矩形02の上辺
	float rect02_max_y = collider_02_.posY + collider_02_.height;	//矩形02の下辺

	if (rect01_min_x <= rect02_max_x &&		//01の左辺が02の右辺より左にある
		rect02_min_x <= rect01_max_x &&		//02の左辺が01の右辺より右にある
		rect01_min_y <= rect02_max_y &&		//01の上辺が02の下辺より下にある
		rect02_min_y <= rect01_max_y)		//02の上辺が01の下辺より上にある
	{
		return false;	//当たっていない
	}
	return true;		//当たっている
}

//円と円の当たり判定用関数
bool OnCollisionCircleToCircle(CircleCollider collider_01_, CircleCollider collider_02_)
{
	float circleToCircle_x = collider_01_.posX - collider_02_.posX;		//01と02間のX座標の距離
	float circleToCircle_y = collider_01_.posY - collider_02_.posY;		//01と02間のY座標の距離

	float length = sqrtf(circleToCircle_x * circleToCircle_x + circleToCircle_y * circleToCircle_y);	//01と02のベクトル

	if (length <= collider_01_.radius + collider_02_.radius)
	{
		return true;	//当たっている

	}
	return false;		//当たっていない

}

//点と矩形の当たり判定用関数
bool OnCollisionPointToRect(RectCollider collider_rect_, int point_x_, int point_y_)
{
	float rect_min_x = collider_rect_.posX;							//矩形の左辺
	float rect_max_x = collider_rect_.posX + collider_rect_.width;	//矩形の右辺
	float rect_min_y = collider_rect_.posY;							//矩形の上辺
	float rect_max_y = collider_rect_.posY + collider_rect_.height;	//矩形の下辺

	if (
		rect_min_x <= point_x_ &&	//矩形の左辺より点の位置が右
		rect_max_x >= point_x_ &&	//矩形の右辺より点の位置が左
		rect_min_y <= point_y_ &&	//矩形の上辺より点の位置が下
		rect_max_y >= point_y_		//矩形の下辺より点の位置が上
		)
	{
		return true;	//当たっている
	}
	return false;	//当たっていない
}
