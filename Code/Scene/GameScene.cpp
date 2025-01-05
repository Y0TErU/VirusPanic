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
	SetBackgroundColor(255, 233, 207);		//背景色変更

	vaccine.Initialize();
	timer.Initialize();
	InitializeEnemies(virus);
	InitializeFriends(whiteBloodCell);
	
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
	if (timer.GetCurrentCounter() == 0)	//初期生成
	{
		CreateEnemies(virus);
		CrateFriends(whiteBloodCell,5);
	}
	
	if (timer.GetCurrentCounter() % 960 == 0 && timer.GetCurrentCounter() != 0)
	{
		CrateFriends(whiteBloodCell,1);		//16秒ごとに生成する
	}
	
	//以下をもっときれいにする -------------------------------------------------------------------------
	//Enemy、Playerと白血球の当たり判定
	for (int i = 0; i < FriendMaxNum; i++)
	{
		vaccine.ToFriend(whiteBloodCell[i].GetIsActive(),whiteBloodCell[i].GetCurrentState(), whiteBloodCell[i].GetTopCollider(), whiteBloodCell[i].GetBotomCollider(),
			whiteBloodCell[i].GetLeftCollider(), whiteBloodCell[i].GetRightCollider());
		if (vaccine.TouchFriend(whiteBloodCell[i].GetIsActive(), whiteBloodCell[i].GetCurrentState()) == true)
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
				while (true)
				{
					if (virus[j].GetIsActive() == false)
					{
						virus[j].Create(whiteBloodCell[i].GetPosX(), whiteBloodCell[i].GetPosY());
						break;
					}
					j++;
				}
			}
		}
	}

	//PlayerとEnemyの当たり
	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].ToPlayer(&vaccine);
	}
	
	//更新処理
	timer.Update();	//時間の更新
	vaccine.Update();	//プレイヤーの更新

	//白血球の更新処理
	ChangeStateFriend(whiteBloodCell);
	UpdateFriends(whiteBloodCell);
	//EraseFriend(whiteBloodCell);
	
	if (whiteBloodCell[SearchTiredFriend(whiteBloodCell)].GetCurrentState() == true)
	{
		UpdateEnemies(virus, &whiteBloodCell[SearchTiredFriend(whiteBloodCell)]);
	}
	else	//いたらターゲットの変更
	{
		UpdateEnemies(virus, &vaccine);
	}

	if (EnemyToEnemy(virus) == true)
	{
		for (int i = 0; i < EnemyMaxNum; i++)
		{
			for (int j = i + 1; j < EnemyMaxNum; j++)
			{
				if (virus[i].GetIsActive() == true && virus[j].GetIsActive() == true)
				{
					virus[i].ToEnemy(&virus[j]);
				}
				
			}
		}
	}
	
	//描画処理
	ClearDrawScreen();

	stage.Draw();		//ステージ

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].Draw();	//ウイルス
	}
	for (int i = 0; i < FriendMaxNum; i++)
	{
		whiteBloodCell[i].Draw();	//白血球
	}

	vaccine.DrawSpaceKey(&whiteBloodCell[SearchTiredFriend(whiteBloodCell)]);	//スペースキー

	vaccine.Draw();		//ワクチン

	timer.Draw();	//時間

	PlayAnimation(whiteBloodCell);

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