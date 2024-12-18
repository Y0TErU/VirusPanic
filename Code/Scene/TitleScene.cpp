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
	SetBackgroundColor(255, 233, 207);		//背景色変更

	int start_text_handle = LoadGraph("Res/Text/start_write.png");


	SetMouseDispFlag(TRUE);	//マウスを表示

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
	SetMouseDispFlag(FALSE);	//マウスを非表示にする

	g_CurrentSceneStep = init;
	g_CurrentSceneType = game;
}