#pragma once

#include "../Collider/Collider.h"

#include <Dxlib.h>

class ObjBase
{
public:
	//�����o�C�j�V�����C�U
	ObjBase()
	{
		posX = 0;			//X���W
		posY = 0;			//Y���W
		width = 0;			//����
		height = 0;			//�c��
		speed = 0.0f;		//���x
		isActive = false;	//�����t���O	
		currentState = false;	//friend�݂̂Ŏg�p(���Ă���󋵂��ǂ���)
		handle_front = -1;	//���ʂ̉摜
		handle_left = -1;	//���̉摜
		handle_right = -1;	//���̉摜
		handle_back = -1;	//���̉摜

		rect_collider =
		{
			posX,posY,
			width,height
		};
	}

	//�I�u�W�F�N�g�̏���
	virtual void Initialize() = 0;	//������
	virtual void Draw() = 0;		//�`��
	void Delete()					//�`��̍폜
	{
		DeleteGraph(handle_front);
		DeleteGraph(handle_right);
		DeleteGraph(handle_left);
		DeleteGraph(handle_back);
	}

	//�Q�b�^�[
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

	//�Z�b�^�[
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
	int posX;			//X���W
	int posY;			//Y���W
	int width;
	int height;
	float speed;		//���x
	bool isActive;		//�����t���O
	bool currentState;	//���Ă��邩�ǂ��� �ifalse�͌��C��ԁAtrue�͔��Ă���j

	RectCollider rect_collider;	//�����蔻��p	

	//�`��n���h��
	int handle_front;	//���ʂ̉摜
	int handle_right;	//�E�����̉摜
	int handle_left;	//�������̉摜
	int handle_back;	//���̉摜
	
};