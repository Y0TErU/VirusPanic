#include "Scene.h"
#include "TitleScene.h"
#include "../Object/Ui.h"
#include "../Object/Operation.h"

#include <Dxlib.h>
#include <math.h>

extern SceneType g_CurrentSceneType;
extern SceneStep g_CurrentSceneStep;

Button textStart;
Button operation;
Operation operation_Display;

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
	int operation_handle = LoadGraph("Res/Text/Operation instructions.png");
	int button_handle = LoadGraph("Res/Button/Start.png");

	SetMouseDispFlag(TRUE);	//�}�E�X��\��

	textStart.Initialize();
	operation.Initialize();
	operation_Display.Initialize();

	textStart.LoadTexture(button_handle,start_text_handle);
	operation.LoadTexture(button_handle,operation_handle);

	g_CurrentSceneStep = update;
}

void UpdateTitleScene()
{
	textStart.Update(660, 700, 600, 150);	//�X�^�[�g�{�^��
	operation.Update(660, 850, 600, 150);	//��������{�^��

	if (operation.GetMouseClick() == true)
	{
		operation_Display.SetIsActive(true);
	}

	if (CheckHitKey(KEY_INPUT_SPACE) && operation_Display.GetIsActive() == true)
	{
		operation_Display.SetIsActive(false);
	}

	ClearDrawScreen();

	textStart.Draw();
	operation.Draw();

	operation_Display.Display();	//����������

	ScreenFlip();
	
	if (textStart.GetMouseClick() == true)
	{
		g_CurrentSceneStep = teminate;
	}
}

void TerminateTitleScene()
{
	SetMouseDispFlag(FALSE);	//�}�E�X���\���ɂ���

	textStart.Delete();
	operation.Delete();

	g_CurrentSceneStep = init;
	g_CurrentSceneType = game;
}