#include "Scene.h"
#include "GameScene.h"

#include "../Object/Enemy.h"
#include "../Object/Player.h"
#include "../Object/Friend.h"
#include "../Object/Stage.h"
#include "../Object/Timer.h"

#include <Dxlib.h>
#include <math.h>

extern SceneType g_CurrentSceneType;
extern SceneStep g_CurrentSceneStep;
extern int g_nextScene;

Player vaccine;
Enemy virus[EnemyMaxNum];
Friend whiteBloodCell[FriendMaxNum];
Timer timer;

Stage stage;


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
	//初期化処理
	g_count = 0;
	friend_Counter = 0;

	vaccine.Initialize();
	timer.Initialize();

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].Initialize();
	}
	for (int i = 0; i < FriendMaxNum; i++)
	{
		whiteBloodCell[i].Initialize();
	}
	
	//描画の読み込み
	vaccine.LoadTexture();
	vaccine.LoadUiTexture();
	timer.Load();

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].LoadTexture();
	}
	for (int i = 0; i < FriendMaxNum; i++)
	{
		whiteBloodCell[i].LoadTexture();
	}

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
	timer.Update();

	vaccine.Update();
	
	ChangeStateFriend(whiteBloodCell);

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
		vaccine.ToFriend(whiteBloodCell[i].GetCurrentState(), whiteBloodCell[i].GetTopCollider(), whiteBloodCell[i].GetBotomCollider(),
			whiteBloodCell[i].GetLeftCollider(), whiteBloodCell[i].GetRightCollider());
		if (vaccine.TouchFriend(whiteBloodCell[i].GetIsActive()) == true && whiteBloodCell[i].GetCurrentState() == true)
		{
			whiteBloodCell[i].SetIsActive(false);
		}
	}

	//時間計測用
	g_count++;

	//描画処理
	ClearDrawScreen();

	stage.Draw();
	vaccine.Draw();
	vaccine.DrawSpaceKey();

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].Draw();
	}
	for (int i = 0; i < FriendMaxNum; i++)
	{
		whiteBloodCell[i].Draw();
	}

	timer.Draw();

	ScreenFlip();
	
	if (vaccine.GetIsActive() == false)
	{
		g_CurrentSceneStep = teminate;
		g_nextScene = over;
	}
	
	
	if (timer.GetCurrentSecond() == 180)
	{
		g_CurrentSceneStep = teminate;
		g_nextScene = clear;
	}
	
	
}

void TerminateGameScene()
{
	vaccine.Delete();
	vaccine.DeleteSpaceKey();
	timer.Delete();
	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].Delete();
	}
	for (int i = 0; i < FriendMaxNum; i++)
	{
		whiteBloodCell[i].Delete();
	}
	

	if (g_nextScene == clear)
	{
		g_CurrentSceneStep = init;
		g_CurrentSceneType = clear;
	}
	else if (g_nextScene == over)
	{
		g_CurrentSceneStep = init;
		g_CurrentSceneType = over;
	}
	
}