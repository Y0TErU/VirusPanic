#include "Scene.h"
#include "OverScene.h"
#include "../Object/Ui.h"

#include <Dxlib.h>

extern SceneType g_CurrentSceneType;
extern SceneStep g_CurrentSceneStep;

extern int g_nextScene;	//次のシーン

Button textTitle;
Button textReplay;

void ExecuteOverScene()
{
	switch (g_CurrentSceneStep)
	{
	case init:
		InitializeOverScene();
		break;

	case update:
		UpdateOverScene();
		break;

	case teminate:
		TerminateOverScene();
		break;
	}

}
void InitializeOverScene()
{
	SetBackgroundColor(0, 0, 0);

	int title_text_handle = LoadGraph("Res/Text/returntitle_write.png");
	int replay_text_handle = LoadGraph("Res/Text/onemoreplay_write.png");
	int bitton_handle = LoadGraph("Res/Button/Start.png");

	SetMouseDispFlag(TRUE);	//マウスを表示

	textTitle.LoadTexture(bitton_handle, title_text_handle);
	textReplay.LoadTexture(bitton_handle, replay_text_handle);

	textTitle.Initialize();
	textReplay.Initialize();

	g_nextScene = 0;

	g_CurrentSceneStep = update;
}
void UpdateOverScene()
{

	textTitle.Update(660, 700, 600, 150);
	textReplay.Update(660, 900, 600, 150);

	ClearDrawScreen();

	textTitle.Draw();
	textReplay.Draw();

	ScreenFlip();

	if (textTitle.GetMouseClick() == true)
	{
		g_CurrentSceneStep = teminate;
		g_nextScene = title;
	}
	if (textReplay.GetMouseClick() == true)
	{
		g_CurrentSceneStep = teminate;
		g_nextScene = game;
	}

}
void TerminateOverScene()
{
	SetMouseDispFlag(FALSE);	//マウスを非表示にする

	g_CurrentSceneStep = init;
	if (g_nextScene == title)
	{
		g_CurrentSceneType = title;
	}
	else if (g_nextScene == game)
	{
		g_CurrentSceneType = game;
	}
}