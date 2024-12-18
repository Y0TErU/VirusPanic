#include "Ui.h"
#include "../Function/MouaseCursor.h"

#include <Dxlib.h>

void Button::LoadTexture(int handle_)
{
	handle = handle_;
}

void Button::Initialize()
{
	mouseClick = false;
}

void Button::Update(int pos_x_, int pos_y_, int width_, int height_)
{
	mouseClick = false;

	const float magnification{ 1.2f };	//拡大率

	posX = pos_x_;
	posY = pos_y_;
	width = width_;
	height = height_;
	buttonCollider =
	{
		posX,posY,
		width,height
	};

	//マウスカーソルが合っている間拡大（1.2倍）
	if (OnCollisionPointToRect(buttonCollider, GetMousePosX(), GetMousePosY()) == true)
	{
		float enlargementWidth = (float)width * magnification;
		float enlargementHeight = (float)height * magnification;

		posX = posX - ((enlargementWidth - width) / 2);
		posY = posY - ((enlargementHeight - height) / 2);
		width = enlargementWidth;
		height = enlargementHeight;
		if (IsMouseClick() == true)
		{
			
			mouseClick = true;
			
		}
	}
}

void Button::Draw()
{
	DrawExtendGraph(posX, posY, posX + width, posY + height, handle, true);
}