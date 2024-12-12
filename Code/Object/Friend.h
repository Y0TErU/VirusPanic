#pragma once

#include "ObjBase.h"
#include "../Collider/Collider.h"

Stage FriendToStage;
const int FriendMaxNum{ 15 };

class Friend : public ObjBase
{
public:
	void Initialize();
	void Create(int pos_x_, int pos_y_);
	void LoadTexture();		//�`��̓ǂݍ���
	void Update();			//�X�V����
	void Draw() override;	//�`�揈��

private:
	const int createInterval{ 660 };
	int friendCounter{ 0 };
	int createConter{ 0 };
	float height;	//�c��
	float width;	//����

	enum State
	{
		fine,
		tired
	};

	RectCollider enemyCollider
	{
		posX,posY,
		width,height
	};
};

void InitializeFriend(Friend* friend_[FriendMaxNum]);
void CreateFriend(Friend* friend_[FriendMaxNum]);


