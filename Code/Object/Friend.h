#pragma once

#include "ObjBase.h"
#include "../Collider/Collider.h"


class Friend : public ObjBase
{
public:
	Friend();
	void LoadTexture();		//•`‰æ‚Ì“Ç‚İ‚İ
	void Update();	//XVˆ—
	void Draw() override;	//•`‰æˆ—

private:
	int friendCounter{ 0 };
	float height;	//c•
	float width;	//‰¡•

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

void Initialize(Friend* friend_);
void CreateFriend(Friend* friend_,int pos_x_,int pos_y_);


