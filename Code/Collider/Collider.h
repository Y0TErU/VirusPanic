#pragma once

//��`�̔���
struct RectCollider
{
	float posX;		//X���W
	float posY;		//Y���W
	float width;	//����
	float height;	//�c��
};

//�~�̔���
struct CircleCollider
{
	float posX;		//X���W
	float posY;		//Y���W
	float radius;
};

//��`�Ƌ�`�̓����蔻��p�֐�
bool OnCollisionRectToRect(RectCollider collider_01_, RectCollider collider_02_);
//�~�Ɖ~�̓����蔻��p�֐�
bool OnCollisionCircleToCircle(CircleCollider collider_01_, CircleCollider collider_02_);
//�_�Ƌ�`�̓����蔻��p�֐�
bool OnCollisionPointToRect(RectCollider collider_rect_, int point_x, int point_y_);

/*
//�X�e�[�W�Ƃ̓����蔻��
bool OnCollisionStageToRect(int stage_[mapHeight][mapwidth],
	int min_x_, int max_x_, int min_y_, int max_y_, float vec_x_, float vec_y_, float* side_x_, float* side_y_);
//�X�e�[�W�̂ǂ̕ӂɓ����邩�𔻒�
bool OnCollisionStageAndRect(int stage_[mapHeight][mapwidth],
	RectCollider rect_, float vec_x_, float vec_y_, float* side_x_, float* side_y_);

*/
