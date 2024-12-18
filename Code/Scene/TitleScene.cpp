#include "Scene.h"
#include "TitleScene.h"
#include "../Object/Ui.h"

#include <Dxlib.h>
#include <math.h>

extern SceneType g_CurrentSceneType;
extern SceneStep g_CurrentSceneStep;

Button textStart;

void ExecuteTitleScene()
{
	switch (g_CurrentSceneStep)
	{
	case init:
		InitializeTitleScene();
		break;

	case update:
		UpdateTitleScene();
		break;

	case teminate:
		TerminateTitleScene();
		break;
	}
}

void InitializeTitleScene()
{
	SetBackgroundColor(255, 233, 207);		//�w�i�F�ύX

	int start_text_handle = LoadGraph("Res/Text/start_write.png");


	SetMouseDispFlag(TRUE);	//�}�E�X��\��

	textStart.Initialize();
	textStart.LoadTexture(start_text_handle);

	g_CurrentSceneStep = update;
}

void UpdateTitleScene()
{
	textStart.Update(660, 700, 600, 150);


	ClearDrawScreen();

	textStart.Draw();

	ScreenFlip();
	
	if (textStart.GetMouseClick() == true)
	{
		g_CurrentSceneStep = teminate;
	}
}

void TerminateTitleScene()
{
	SetMouseDispFlag(FALSE);	//�}�E�X���\���ɂ���

	g_CurrentSceneStep = init;
	g_CurrentSceneType = game;
}