#pragma once

#include "ObjBase.h"
#include "../Collider/Collider.h"

const int FriendMaxNum{ 15 };

class Friend : public ObjBase
{
public:
	void Initialize();
	void Create();
	void LoadTexture();		//•`‰æ‚Ì“Ç‚İ‚İ
	void Update();			//XVˆ—
	void Draw() override;	//•`‰æˆ—

	int GetCurrentState()
	{
		return currentState;
	}

private:
	const int createInterval{ 960 };
	const int changeStateInterval{ 660 };
	int currentState{ fine };
	int friendCounter{ 0 };
	int timeCount{ 0 };
	float height{ 96 };	//c•
	float width{ 96 };	//‰¡•

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


