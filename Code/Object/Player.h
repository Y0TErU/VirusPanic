#pragma once

#include "ObjBase.h"

class Player : public ObjBase
{
public:
	void LoadTexture();		//�`��̓ǂݍ���
	void Initialize();		//������
	void Update();	//�X�V����
	void Draw() override;	//�`�揈��


private:
	int nextPosX{ posX };
	int nextPosY{ posY };
	float vecX{ 0.0f };		//�ړ��p�x�N�g��
	float vecY{ 0.0f };
	int height{ 60 };		//�c��
	int width{ 75 };

	
};