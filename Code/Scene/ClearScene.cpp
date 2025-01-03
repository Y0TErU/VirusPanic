#include "Scene.h"
#include "ClearScene.h"
#include "../Object/Ui.h"

#include <Dxlib.h>
#include <math.h>

extern SceneType g_CurrentSceneType;
extern SceneStep g_CurrentSceneStep;

Button textClear;
Button forTitle;

int handle_Clear = -1;
int handle_Break = -1;
int handle_Bg = -1;

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
	
	int handle_forTitle = LoadGraph("Res/Text/returntitle_write.png");
	int handle_button = LoadGraph("Res/Button/Icon_SquareStraight.png");

	handle_Clear = LoadGraph("Res/Text/gameclear_write.png");
	handle_Break = LoadGraph("Res/Text/wakutin_win.png");
	handle_Bg = LoadGraph("Res/Ui/ClearBackGround.png");

	SetMouseDispFlag(TRUE);	//マウスを表示
	forTitle.LoadTexture(handle_button, handle_forTitle);


	g_CurrentSceneStep = update;
}

void UpdateClearScene()
{
	forTitle.Update(660, 700, 600, 150);

	ClearDrawScreen();
	

	DrawExtendGraph(0, 0, 1920, 1080, handle_Bg, true);
	DrawGraph(530,200, handle_Break,true);
	DrawGraph(580, 50, handle_Clear, true);

	forTitle.Draw();


	ScreenFlip();

	if (forTitle.GetMouseClick() == true)
	{
		g_CurrentSceneStep = teminate;
	}
}

void TerminateClearScene()
{
	SetMouseDispFlag(FALSE);	//マウスを非表示にする

	forTitle.Delete();
	DeleteGraph(handle_Break);
	DeleteGraph(handle_Clear);
	DeleteGraph(handle_Bg);

	g_CurrentSceneStep = init;
	g_CurrentSceneType = title;
}