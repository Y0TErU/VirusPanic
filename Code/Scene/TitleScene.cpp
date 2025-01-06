#include "Scene.h"
#include "TitleScene.h"
#include "../Object/Ui.h"
#include "../Object/Operation.h"
#include "../Sound/Sound.h"

#include <Dxlib.h>
#include <math.h>

extern SceneType g_CurrentSceneType;
extern SceneStep g_CurrentSceneStep;

Button textStart;
Button operation;
Operation operation_Display;
Text virusPanic;
Text SpaceKey;

Sound titleSound;
Sound pushSpace;

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
	int operation_handle = LoadGraph("Res/Text/Operation instructions.png");
	int button_handle = LoadGraph("Res/Button/Start.png");
	int title_handle = LoadGraph("Res/Text/title_write.png");
	int space_key_handle = LoadGraph("Res/Ui/Ui_space.png");

	int title_s_handle = LoadSoundMem("Sound/title.m4a");
	int push_s_handle = LoadSoundMem("Sound/button_kettei.m4a");

	SetMouseDispFlag(TRUE);	//マウスを表示

	textStart.Initialize();
	operation.Initialize();
	operation_Display.Initialize();
	SpaceKey.Initialize(1780,1000,120,50, space_key_handle);

	virusPanic.Initialize(280, 200, 1360, 332, title_handle);

	textStart.LoadTexture(button_handle,start_text_handle);
	operation.LoadTexture(button_handle,operation_handle);

	titleSound.Load(title_s_handle);
	pushSpace.Load(push_s_handle);

	g_CurrentSceneStep = update;
}

void UpdateTitleScene()
{
	static int counter = 0;
	static bool operation_isActive = false;

	titleSound.LoopPlay();

	if (operation_isActive == false)
	{
		textStart.Update(660, 650, 600, 150);	//スタートボタン
		operation.Update(660, 850, 600, 150);	//操作説明ボタン
	}
	

	if (operation.GetMouseClick() == true)
	{
		operation_Display.SetIsActive(true);
		operation_isActive = true;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) && operation_Display.GetIsActive() == true)
	{
		pushSpace.BackGroundPlay();
		operation_Display.SetIsActive(false);
		operation_isActive = false;
	}


	ClearDrawScreen();

	if (operation_isActive == true)
	{
		operation_Display.Display();	//操作説明画面
		if (counter < 30)
		{
			SpaceKey.Draw();
		}
		else if (counter > 60)
		{
			counter = 0;
		}
	}
	else
	{
		textStart.Draw();
		operation.Draw();
		virusPanic.Draw();
	}

	ScreenFlip();

	counter++;
	
	if (textStart.GetMouseClick() == true)
	{
		g_CurrentSceneStep = teminate;
		counter = 0;
	}
}

void TerminateTitleScene()
{
	SetMouseDispFlag(FALSE);	//マウスを非表示にする

	textStart.Delete();
	operation.Delete();
	virusPanic.Delete();
	titleSound.Delete();
	pushSpace.Delete();

	g_CurrentSceneStep = init;
	g_CurrentSceneType = game;
}