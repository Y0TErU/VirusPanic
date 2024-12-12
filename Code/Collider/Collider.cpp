#include <Dxlib.h>
#include <math.h>

#include "Collider.h"

//��`�Ƌ�`�̓����蔻��p�֐�
bool OnCollisionRectToRect(RectCollider collider_01_, RectCollider collider_02_)
{
	float rect01_min_x = collider_01_.posX;							//��`01�̍���
	float rect01_max_x = collider_01_.posX + collider_01_.width;	//��`01�̉E��
	float rect01_min_y = collider_01_.posY;							//��`01�̏��
	float rect01_max_y = collider_01_.posY + collider_01_.height;	//��`01�̉���

	float rect02_min_x = collider_02_.posX;							//��`02�̍���
	float rect02_max_x = collider_02_.posX + collider_02_.width;	//��`02�̉E��
	float rect02_min_y = collider_02_.posY;							//��`02�̏��
	float rect02_max_y = collider_02_.posY + collider_02_.height;	//��`02�̉���

	if (rect01_min_x <= rect02_max_x &&		//01�̍��ӂ�02�̉E�ӂ�荶�ɂ���
		rect02_min_x <= rect01_max_x &&		//02�̍��ӂ�01�̉E�ӂ��E�ɂ���
		rect01_min_y <= rect02_max_y &&		//01�̏�ӂ�02�̉��ӂ�艺�ɂ���
		rect02_min_y <= rect01_max_y)		//02�̏�ӂ�01�̉��ӂ���ɂ���
	{
		return false;	//�������Ă��Ȃ�
	}
	return true;		//�������Ă���
}

//�~�Ɖ~�̓����蔻��p�֐�
bool OnCollisionCircleToCircle(CircleCollider collider_01_, CircleCollider collider_02_)
{
	float circleToCircle_x = collider_01_.posX - collider_02_.posX;		//01��02�Ԃ�X���W�̋���
	float circleToCircle_y = collider_01_.posY - collider_02_.posY;		//01��02�Ԃ�Y���W�̋���

	float length = sqrtf(circleToCircle_x * circleToCircle_x + circleToCircle_y * circleToCircle_y);	//01��02�̃x�N�g��

	if (length <= collider_01_.radius + collider_02_.radius)
	{
		return true;	//�������Ă���

	}
	return false;		//�������Ă��Ȃ�

}

//�_�Ƌ�`�̓����蔻��p�֐�
bool OnCollisionPointToRect(RectCollider collider_rect_, int point_x_, int point_y_)
{
	float rect_min_x = collider_rect_.posX;							//��`�̍���
	float rect_max_x = collider_rect_.posX + collider_rect_.width;	//��`�̉E��
	float rect_min_y = collider_rect_.posY;							//��`�̏��
	float rect_max_y = collider_rect_.posY + collider_rect_.height;	//��`�̉���

	if (
		rect_min_x <= point_x_ &&	//��`�̍��ӂ��_�̈ʒu���E
		rect_max_x >= point_x_ &&	//��`�̉E�ӂ��_�̈ʒu����
		rect_min_y <= point_y_ &&	//��`�̏�ӂ��_�̈ʒu����
		rect_max_y >= point_y_		//��`�̉��ӂ��_�̈ʒu����
		)
	{
		return true;	//�������Ă���
	}
	return false;	//�������Ă��Ȃ�
}
