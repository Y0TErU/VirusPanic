#include "MouaseCursor.h"

#include <Dxlib.h>
#include <math.h>

int GetMousePosX()
{
	int x = 0;
	GetMousePoint(&x, nullptr);
	return x;
}

int GetMousePosY()
{
	int y = 0;
	GetMousePoint(nullptr, &y);
	return y;
}

bool IsMouseClick()
{
	int button;
	int type;

	if (GetMouseInputLog2(&button, nullptr, nullptr, &type) == 0)
	{
		if (type == MOUSE_INPUT_LOG_DOWN)
		{
			return true;
		}
	}
	return false;
}