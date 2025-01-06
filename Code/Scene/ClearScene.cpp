#include "Scene.h"
#include "ClearScene.h"
#include "../Object/Ui.h"

#include "../Sound/Sound.h"

#include <Dxlib.h>
#include <math.h>

extern SceneType g_CurrentSceneType;
extern SceneStep g_CurrentSceneStep;

Button textClear;
Button forTitle;
Text GAMECLEAR;
Text bg_clear;
Text knock_down;

Sound s_gameClear;

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

	int handle_Clear = LoadGraph("Res/Text/gameclear_write.png");
	int handle_knock = LoadGraph("Res/Text/wakutin_win.png");
	int handle_Bg = LoadGraph("Res/Ui/ClearBackGround.png");

	int handle_forTitle = LoadGraph("Res/Text/returntitle_write.png");
	int handle_button = LoadGraph("Res/Button/Icon_SquareStraight.png");

	int clear_s_handle = LoadSoundMem("Sound/gameclear.mp3");

	s_gameClear.Load(clear_s_handle);

	SetMouseDispFlag(TRUE);	//マウスを表示
	forTitle.LoadTexture(handle_button, handle_forTitle);
	GAMECLEAR.Initialize(360, 50, 1200, 293, handle_Clear);

	bg_clear.Initialize(0, 0, 1920, 1080, handle_Bg);
	//knock_down.Initialize(530, 200, 900, 646, handle_knock);
	knock_down.Initialize(555, 320, 810, 582, handle_knock);

	g_CurrentSceneStep = update;
}

void UpdateClearScene()
{
	static bool count = false;

	forTitle.Update(660, 850, 600, 150);

	if (count == false)
	{
		s_gameClear.BackGroundPlay();

		count = true;
	}

	ClearDrawScreen();

	bg_clear.Draw();
	GAMECLEAR.Draw();
	knock_down.Draw();
	forTitle.Draw();

	ScreenFlip();

	if (forTitle.GetMouseClick() == true)
	{
		g_CurrentSceneStep = teminate;
		count = false;
	}
}

void TerminateClearScene()
{
	SetMouseDispFlag(FALSE);	//マウスを非表示にする

	s_gameClear.Delete();

	bg_clear.Delete();
	GAMECLEAR.Delete();
	knock_down.Delete();
	forTitle.Delete();


	g_CurrentSceneStep = init;
	g_CurrentSceneType = title;
}