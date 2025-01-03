#pragma once

#include "../Collider/Collider.h"

class Button
{
public:
	void Initialize();
	void LoadTexture(int handle_button_, int handle_text_);
	void Update(int pos_x_, int pos_y_, int width_, int height_);
	void Draw();
	void Delete();

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
	int handle_button{ -1 };
	int handle_text{ -1 };

	RectCollider buttonCollider
	{
		posX,posY,
		width,height,
	};
};

class Text
{
public:
	void Initialize(int pos_x_,int pos_y_,int width_,int height_,int handle_);
	void Draw();
	void Delete();

private:
	int posX{ 0 };
	int posY{ 0 };
	int width{ 0 };
	int height{ 0 };
	int handle{ -1 };
};