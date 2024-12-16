#pragma once

#include "ObjBase.h"
#include "../Collider/Collider.h"

const int FriendMaxNum{ 15 };
const int initialFriendNum{ 5 };

class Friend : public ObjBase
{
public:
	void Initialize() override;	//������
	void Create();				//����
	void LoadTexture();			//�`��̓ǂݍ���
	void Update();				//�X�V����
	void Draw() override;		//�`�揈��

	//�X�e�[�^�X�̃Q�b�^�[
	bool GetCurrentState()
	{
		return currentState;
	}


private:
	const int createInterval{ 960 };	//�����̎��ԊԊu
	const int changeStateInterval{ 300 };	//��ԕω��̎��ԊԊu
	bool currentState{ false };	//���݂̃X�e�[�^�X(false �͌��C���)
	
	int timeCount{ 0 };
	float height{ 96 };	//�c��
	float width{ 96 };	//����

	RectCollider enemyCollider
	{
		posX,posY,
		width,height
	};
};

//void InitializeFriend(ObjBase* friend_[FriendMaxNum]);

void CreateFriends(Friend* friend_[FriendMaxNum]);


