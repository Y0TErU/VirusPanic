#pragma once

#include "ObjBase.h"

const int FriendMaxNum{ 15 };
const int initialFriendNum{ 5 };


class Friend : public ObjBase
{
public:
	void Initialize() override;	//������
	void Create();				//����
	void LoadTexture();			//�`��̓ǂݍ���
	void Update();				//�X�V����
	void Erace();				//�폜
	void Draw() override;		//�`�揈��

	void PlayAnim();

	//RectCollider�̃Q�b�^�[
	RectCollider* GetTopCollider()
	{
		return &top_collider;	//1�}�X��̍��W
	}
	RectCollider* GetBotomCollider()
	{
		return &botom_collider;	//1�}�X���̍��W
	}
	RectCollider* GetRightCollider()
	{
		return &left_collider;	//1�}�X���̍��W
	}
	RectCollider* GetLeftCollider()
	{
		return &right_collider;	//1�}�X�E�̍��W
	}

	//��ԕω����ɕK�v�ȃQ�b�^�[�ƃZ�b�^�[
	bool GetCanUpdate()
	{
		return canUpdate;
	}

	void SetCanUpdate(bool canUpdate_)
	{
		canUpdate = canUpdate_;
	}

private:
	const int createInterval{ 960 };	//�����̎��ԊԊu
	const int changeStateInterval{ 660 };	//��ԕω��̎��ԊԊu(11�b)
	int timeCount{ 0 };
	int height{ 96 };	//�c��
	int width{ 96 };	//����
	bool canUpdate{ false };	//�X�V�\��
	bool beforeIsActive{ false };	//�P�O�ɐ������Ă��邩�ǂ���

	int handle_tired{ -1 };
	int handle_animation[6]
	{
		-1,-1,-1,-1,-1,-1
	};

	RectCollider top_collider
	{
		posX,posY - height,
		width,height - height
	};
	RectCollider botom_collider
	{
		posX,posY + height,
		width,height + height
	};
	RectCollider left_collider
	{
		posX - width,posY,
		width - width,height
	};
	RectCollider right_collider
	{
		posX + width,posY,
		width + width,height
	};
};

void InitializeFriends(Friend* friend_);			//������
void ChangeStateFriend(Friend* friend_);			//��ԕω�(���Ă���)
void CrateFriends(Friend* friend_,int create_num_);	//����
void UpdateFriends(Friend* friend_);				//�X�V
int SearchTiredFriend(Friend* friend_);				//���Ă���I�u�W�F�N�g��T��
//void EraseFriend(Friend* friend_);					//�����t���O�������Ă��Ȃ��I�u�W�F�N�g������

void PlayAnimation(Friend* friend_);