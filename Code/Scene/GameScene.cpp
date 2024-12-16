#include "Scene.h"
#include "GameScene.h"

#include "../Object/Enemy.h"
#include "../Object/Player.h"
#include "../Object/Friend.h"
#include "../Object/Stage.h"

#include <Dxlib.h>
#include <math.h>

extern SceneType g_CurrentSceneType;
extern SceneStep g_CurrentSceneStep;
extern int g_nextScene;

Player vaccine;
Enemy virus[EnemyMaxNum];
Friend whiteBloodCell[FriendMaxNum];

Stage stage;

int g_time_handle = -1;
int g_clock_handle = -1;

int g_count = 0;

int friend_Counter;

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
	
	vaccine.LoadTexture();

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].LoadTexture();
	}
	for (int i = 0; i < FriendMaxNum; i++)
	{
		whiteBloodCell[i].LoadTexture();
	}
	
	//初期化処理
	g_count = 0;
	friend_Counter = 0;

	vaccine.Initialize();

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].Initialize();
	}
	for (int i = 0; i < FriendMaxNum; i++)
	{
		whiteBloodCell[i].Initialize();
	}
	
	//描画の読み込み
	g_time_handle = LoadGraph("Res/Digit01.png");
	g_clock_handle = LoadGraph("Res/Icon_Clock.png");

	g_CurrentSceneStep = update;
}

void UpdateGameScene()
{

	//生成処理
	if (g_count == 0)	//初期生成
	{
		for (int i = 0; i < EnemyMaxNum; i++)
		{
			virus[i].Create((int)virus->GetPosX(), (int)virus->GetPosY());
			break;
		}
		for (int i = 0; i < initialFriendNum; i++)
		{
			whiteBloodCell[i].Create();
			friend_Counter = i;
		}
	}
	
	if (g_count % 180 == 0 && g_count != 0)
	{
		friend_Counter++;
		whiteBloodCell[friend_Counter].Create();
		
	}
	/*
	if (g_count % 960 == 0 && g_count != 0)
	{
		for (int i = 0; i < FriendMaxNum; i++)
		{
			whiteBloodCell[i].Create();
			break;
		}
	}
	*/
	
	//更新処理
	vaccine.Update();

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		if (whiteBloodCell[i].GetCurrentState() == false)
		{
			virus[i].Update(&vaccine);
		}
		else
		{
			virus[i].Update(&whiteBloodCell[i]);
			virus[i].ToFriend(&whiteBloodCell[i]);
		}
		
	}
	for (int i = 0; i < FriendMaxNum; i++)
	{
		whiteBloodCell[i].Update();
	}

	//時間計測用
	g_count++;

	//描画処理
	ClearDrawScreen();

	stage.Draw();
	vaccine.Draw();

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].Draw();
	}
	for (int i = 0; i <= FriendMaxNum; i++)
	{
		whiteBloodCell[i].Draw();
	}

	//DrawGraph(200,0,g_time_handle,true);
	//DrawGraph(0,0, g_clock_handle,true);

	ScreenFlip();
	
	if (vaccine.GetIsActive() == false)
	{
		g_CurrentSceneStep = teminate;
		g_nextScene = over;
	}
	
	
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		g_CurrentSceneStep = teminate;
		g_nextScene = clear;
	}
	
	
}

void TerminateGameScene()
{
	vaccine.Delete();
	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].Delete();
	}
	for (int i = 0; i < FriendMaxNum; i++)
	{
		whiteBloodCell[i].Delete();
	}
	
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