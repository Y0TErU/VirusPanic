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
	SetBackgroundColor(255, 233, 207);		//”wŒiF•ÏX

	//‰Šú‰»ˆ—
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
	
	//•`‰æ‚Ì“Ç‚İ‚İ
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

	//¶¬ˆ—
	if (timer.GetCurrentCounter() == 0)	//‰Šú¶¬
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
	
	if (timer.GetCurrentCounter() % 960 == 0 && timer.GetCurrentCounter() != 0)
	{
		friend_Counter++;
		whiteBloodCell[friend_Counter].Create();
		
	}
	
	
	//XVˆ—
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
		for (int j = 0; j < EnemyMaxNum; j++)
		{
			virus[j].ToFriend(whiteBloodCell[i].GetCurrentState(), whiteBloodCell[i].GetTopCollider(), whiteBloodCell[i].GetBotomCollider(),
				whiteBloodCell[i].GetLeftCollider(), whiteBloodCell[i].GetRightCollider());
			if (virus[j].TouchFriend(whiteBloodCell[i].GetIsActive()) == true && whiteBloodCell[i].GetCurrentState() == true)
			{
				whiteBloodCell[i].SetIsActive(false);
			}
		}
		
	}


	//•`‰æˆ—
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
	
	if (vaccine.GetIsActive() == false || CheckHitKey(KEY_INPUT_RETURN))
	{
		g_CurrentSceneStep = teminate;
		g_nextScene = over;
	}
	
	
	if (timer.GetCurrentCounter() == 10800 || CheckHitKey(KEY_INPUT_TAB))
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