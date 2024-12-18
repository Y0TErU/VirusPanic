#pragma once

//��`�̔���
struct RectCollider
{
	int posX;	//X���W
	int posY;	//Y���W
	int width;	//����
	int height;	//�c��
};

//�~�̔���
struct CircleCollider
{
	int posX;	//X���W
	int posY;	//Y���W
	int radius;
};

//��`�Ƌ�`�̓����蔻��p�֐�
bool OnCollisionRectToRect(RectCollider collider_01_, RectCollider collider_02_);
//�~�Ɖ~�̓����蔻��p�֐�
bool OnCollisionCircleToCircle(CircleCollider collider_01_, CircleCollider collider_02_);
//�_�Ƌ�`�̓����蔻��p�֐�
bool OnCollisionPointToRect(RectCollider collider_rect_, int point_x, int point_y_);

