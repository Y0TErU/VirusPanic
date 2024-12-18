#pragma once

#include "../Collider/Collider.h"

class Button
{
public:
	void Initialize();
	void LoadTexture(int handle_);
	void Update(int pos_x_, int pos_y_, int width_, int height_);
	void Draw();

	bool GetMouseClick()
	{
		return mouseClick;
	}

private:
	bool mouseClick{ false };
	int posX{ 0 };
	int posY{ 0 };
	int height{ 0 };
	int width{ 0 };
	int handle{ -1 };
	RectCollider buttonCollider
	{
		posX,posY,
		width,height,
	};
};