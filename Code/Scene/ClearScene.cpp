#include "Scene.h"
#include "ClearScene.h"
#include "../Object/Ui.h"

#include <Dxlib.h>
#include <math.h>

extern SceneType g_CurrentSceneType;
extern SceneStep g_CurrentSceneStep;

Button textClear;

int g_handle = -1;

void ExecuteClearScene()
{
	switch (g_CurrentSceneStep)
	{
	case init:
		InitializeClearScene();
		break;

	case update:
		UpdateClearScene();
		break;

	case teminate:
		TerminateClearScene();
		break;
	}
}

void InitializeClearScene()
{
	SetBackgroundColor(255, 255, 255);
	
	int handle_Clear = LoadGraph("Res/Text/returntitle_write.png");

	SetMouseDispFlag(TRUE);	//�}�E�X��\��
	textClear.LoadTexture(handle_Clear);

	g_CurrentSceneStep = update;
}

void UpdateClearScene()
{
	textClear.Update(660, 700, 600, 150);

	ClearDrawScreen();

	DrawGraph(0, 0, g_handle, true);
	textClear.Draw();

	ScreenFlip();

	if (textClear.GetMouseClick() == true)
	{
		g_CurrentSceneStep = teminate;
	}
}

void TerminateClearScene()
{
	SetMouseDispFlag(FALSE);	//�}�E�X���\���ɂ���

	DeleteGraph(g_handle);

	g_CurrentSceneStep = init;
	g_CurrentSceneType = title;
}