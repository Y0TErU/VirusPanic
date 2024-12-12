#pragma once

#include "../Collider/Collider.h"

class Button
{
public:
	void LoadTexture(int handle_);
	void Update(float pos_x_, float pos_y_, float width_, float height_);
	void Draw();

	bool GetMouseClick()
	{
		return mouseClick;
	}

private:
	bool mouseClick{ false };
	float posX{ 0 };
	float posY{ 0 };
	float height{ 0 };
	float width{ 0 };
	int handle{ -1 };
	RectCollider buttonCollider
	{
		posX,posY,
		width,height,
	};
};