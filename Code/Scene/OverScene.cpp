#include "Scene.h"
#include "OverScene.h"
#include "../Object/Ui.h"
#include "../Sound/Sound.h"

#include <Dxlib.h>

extern SceneType g_CurrentSceneType;
extern SceneStep g_CurrentSceneStep;

extern int g_nextScene;	//次のシーン

Button textTitle;
Button textReplay;
Text GAMEOVER;

Sound s_gameOver;

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
	int gameover_handle = LoadGraph("Res/Text/gameover_write.png");

	int over_s_shandle = LoadSoundMem("Sound/gameover.m4a");

	s_gameOver.Load(over_s_shandle);

	SetMouseDispFlag(TRUE);	//マウスを表示

	textTitle.LoadTexture(bitton_handle, title_text_handle);
	textReplay.LoadTexture(bitton_handle, replay_text_handle);

	textTitle.Initialize();
	textReplay.Initialize();
	GAMEOVER.Initialize(360, 200, 1200, 293, gameover_handle);

	g_nextScene = 0;

	g_CurrentSceneStep = update;
}
void UpdateOverScene()
{
	static bool count = false;

	textTitle.Update(660, 900, 600, 150);
	textReplay.Update(660, 700, 600, 150);

	if (count == false)
	{
		s_gameOver.BackGroundPlay();
		count = true;
	}

	ClearDrawScreen();

	textTitle.Draw();
	textReplay.Draw();
	GAMEOVER.Draw();

	ScreenFlip();

	if (textTitle.GetMouseClick() == true)
	{
		g_CurrentSceneStep = teminate;
		g_nextScene = title;
		count = false;
	}
	if (textReplay.GetMouseClick() == true)
	{
		g_CurrentSceneStep = teminate;
		g_nextScene = game;
		count = false;
	}

}
void TerminateOverScene()
{
	SetMouseDispFlag(FALSE);	//マウスを非表示にする

	GAMEOVER.Delete();
	textTitle.Delete();
	textReplay.Delete();
	s_gameOver.Delete();

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