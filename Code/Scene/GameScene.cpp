#include "Scene.h"
#include "GameScene.h"

#include "../Object/Enemy.h"
#include "../Object/Player.h"
#include "../Object/Stage.h"

#include <Dxlib.h>
#include <math.h>

extern SceneType g_CurrentSceneType;
extern SceneStep g_CurrentSceneStep;
extern int g_nextScene;

Player vaccine;
Enemy virus;
//Friend whiteBloodCell[maxFriendNum];

Stage stage;

int g_time_handle = -1;
int g_clock_handle = -1;

int g_count = 0;

void ExecuteGameScene()
{
	switch (g_CurrentSceneStep)
	{
	case init:
		InitializeGameScene();
		break;

	case update:
		UpdateGameScene();
		break;

	case teminate:
		TerminateGameScene();
		break;
	}
}

void InitializeGameScene()
{
	//画像読み込み処理
	g_count = 0;
	vaccine.LoadTexture();
	virus.LoadTexture();
	g_time_handle = LoadGraph("Res/Digit01.png");
	g_clock_handle = LoadGraph("Res/Icon_Clock.png");

	g_CurrentSceneStep = update;
}

void UpdateGameScene()
{
		//時間計測用

	//更新処理
	vaccine.Update();

	virus.Update(&vaccine);


	g_count++;

	//描画処理
	ClearDrawScreen();

	stage.Draw();
	vaccine.Draw();
	virus.Draw();
	DrawGraph(200,0,g_time_handle,true);
	DrawGraph(0,0, g_clock_handle,true);

	ScreenFlip();
	
	if (CheckHitKey(KEY_INPUT_TAB))
	{
		g_CurrentSceneStep = teminate;
		g_nextScene = over;
	}
	
	
	if (g_count >= 180)
	{
		g_CurrentSceneStep = teminate;
		g_nextScene = clear;
	}
	
	
}

void TerminateGameScene()
{
	vaccine.Delete();
	virus.Delete();
	DeleteGraph(g_time_handle);

	if (g_nextScene == clear)
	{
		g_CurrentSceneStep = init;
		g_CurrentSceneType = clear;
	}
	if (g_nextScene == over)
	{
		g_CurrentSceneStep = init;
		g_CurrentSceneType = over;
	}
	
}