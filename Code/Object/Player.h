#pragma once

#include "ObjBase.h"

class Player : public ObjBase
{
public:
	void LoadTexture();		//�`��̓ǂݍ���
	void Initialize();		//������
	void Update();		//�X�V����
	void Draw() override;	//�`�揈��

	//ui�֌W�̊֐�
	void LoadUiTexture();	//SPACE_KEY��UI
	void DrawSpaceKey();	
	void DeleteSpaceKey();

	//�������Ƃ̔���p
	void ToFriend(bool isActive_, bool isTouch_, RectCollider* friend_top_, RectCollider* friend_botom_, RectCollider* friend_left_, RectCollider* friend_right_);
	bool TouchFriend(bool isActive_, bool tired_);

private:
	int nextPosX{ posX };
	int nextPosY{ posY };
	float vecX{ 0.0f };		//�ړ��p�x�N�g��
	float vecY{ 0.0f };
	int height{ 60 };		//�c��
	int width{ 75 };
	bool canTouch{ false };	//�������Ƀ^�b�`�\���ǂ���

	//UI SPACE�L�[
	int handle_space{ -1 };	//UI�n���h��(SPACE)
};