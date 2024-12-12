#pragma once

#include "ObjBase.h"
#include "../Collider/Collider.h"

Stage playerToStage;

class Player : public ObjBase
{
public:
	void LoadTexture();		//�`��̓ǂݍ���
	void Initialize();		//������
	void Update();	//�X�V����
	void Draw() override;	//�`�揈��

private:
	float nextPosX{ posX };
	float nextPosY{ posY };
	float vecX{ 0.0f };		//�ړ��p�x�N�g��
	float vecY{ 0.0f };
	float height{ 50 };	//�c��
	float width{ 75 };

	RectCollider playerCollider		//�����蔻��p
	{
		posX,posY,
		width,height
	};
};