#include "Stage.h"

#include <Dxlib.h>
#include <math.h>
#include <stdlib.h>

void Stage::Draw()
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapwidth; j++)
		{
			posX = j * blockSize + mapOffSetX;
			posY = i * blockSize + mapOffSetY;

			if (stageArrange[i][j] == 0)
			{
				DrawBox(posX,posY,posX + blockSize,posY + blockSize, GetColor(215, 0, 0), true);
			}
			else
			{
				DrawBox(posX,posY,posX + blockSize,posY + blockSize, GetColor(250, 200, 170), true);
			}
		}
	}
}

bool Stage::OnCollisionStageToRect(int min_x_, int max_x_, int min_y_, int max_y_, 
	float vec_x_, float vec_y_, float* side_x_, float* side_y_)
{
	for (int i = min_y_; i <= max_y_; i++)
	{
		for (int j = min_x_; j <= max_x_; j++)
		{
			if (stageArrange[i][j] != 0)
			{
				if (side_x_ != nullptr)
				{
					if (vec_x_ > 0.0f)
					{
						*side_x_ = (j * blockSize) + mapOffSetX;
					}
					else if (vec_x_ < 0.0f)
					{
						*side_x_ = (j * blockSize + blockSize) + mapOffSetX;
					}
				}

				if (side_y_ != nullptr)
				{
					if (vec_y_ > 0.0f)
					{
						*side_y_ = (i * blockSize) + mapOffSetY;
					}
					else if (vec_y_ < 0.0f)
					{
						*side_y_ = (i * blockSize + blockSize) + mapOffSetY;
					}
				}
				return true;
			}
		}
	}
	return false;
}

bool Stage::OnCollisionStageAndRect(RectCollider rect_, float vec_x_, float vec_y_, float* side_x_, float* side_y_)
{
	if (vec_x_ == 0.0f && vec_y_ == 0.0f)
	{
		return false;		//ìÆÇ¢ÇƒÇ¢Ç»Ç¢
	}

	int minX = (rect_.posX - mapOffSetX) / blockSize;						//âEï”
	int maxX = ((rect_.posX + rect_.width) - mapOffSetX) / blockSize;		//ç∂ï”
	int minY = (rect_.posY - mapOffSetY) / blockSize;						//è„ï”
	int maxY = ((rect_.posY + rect_.height)- mapOffSetY) / blockSize;		//â∫ï”
	bool isCollision = false;

	if (vec_x_ > 0.0f)
	{
		isCollision = OnCollisionStageToRect(maxX, maxX,
			minY, maxY, vec_x_, vec_y_, side_x_, side_y_);
	}
	else if (vec_x_ < 0.0f)
	{
		isCollision = OnCollisionStageToRect(minX, minX,
			minY, maxY, vec_x_, vec_y_, side_x_, side_y_);
	}

	if (isCollision == true)
	{
		return true;
	}

	if (vec_y_ < 0.0f)
	{
		isCollision = OnCollisionStageToRect(minX, maxX,
			minY, minY, vec_x_, vec_y_, side_x_, side_y_);
	}
	else if (vec_y_ > 0.0f)
	{
		isCollision = OnCollisionStageToRect(minX, maxX,
			maxY, maxY, vec_x_, vec_y_, side_x_, side_y_);
	}

	return isCollision;
}

void Stage::GetRandomStage()
{
	bool selectedStage = true;
	int vertical;		//èc
	int beside;			//â°

	while (true)
	{
		vertical = rand() % 11;
		beside = rand() % 19;

		if (stageArrange[vertical][beside] == 1)
		{
			stageArrange[vertical][beside] = 2;
			getPosX = mapOffSetX + blockSize * beside;
			getPosY = mapOffSetY + blockSize * vertical;
			break;
		}

	}

	
}

int Stage::GetStagePosX()
{
	return getPosX;
}

int Stage::GetStagePosY()
{
	return getPosY;
}
