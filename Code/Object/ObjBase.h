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
		speed = 0.0f;		//���x
		isActive = false;	//�����t���O
		handle = -1;		//�`��n���h��
	}

	//�I�u�W�F�N�g�̏���
	virtual void Initialize() = 0;	//������
	virtual void Draw() = 0;		//�`��
	void Delete()					//�`��̍폜
	{
		DeleteGraph(handle);
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
	int GetHandle()
	{
		return handle;
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
	float posX;			//X���W
	float posY;			//Y���W
	float speed;		//���x
	bool isActive;		//�����t���O
	int handle;			//�`��n���h��
	
};