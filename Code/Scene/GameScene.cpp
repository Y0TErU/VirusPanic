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
	//�摜�ǂݍ��ݏ���
	
	vaccine.LoadTexture();

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].LoadTexture();
		whiteBloodCell[i].LoadTexture();
	}
	
	//����������
	g_count = 0;

	vaccine.Initialize();

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].Initialize();
	}
	for (int i = 0; i < FriendMaxNum; i++)
	{
		whiteBloodCell[i].Initialize();
	}
	

	//�`��̓ǂݍ���
	g_time_handle = LoadGraph("Res/Digit01.png");
	g_clock_handle = LoadGraph("Res/Icon_Clock.png");

	g_CurrentSceneStep = update;
}

void UpdateGameScene()
{

	//��������
	if (g_count == 0)	//��������
	{
		for (int i = 0; i < EnemyMaxNum; i++)
		{
			virus[i].Create(virus->GetPosX(), virus->GetPosY());
			break;
		}
		for (int i = 0; i < initialFriendNum; i++)
		{
			whiteBloodCell[i].Create();
		}
	}
	
	if (g_count % 960 == 0)
	{
		for (int i = 0; i < FriendMaxNum; i++)
		{
			whiteBloodCell[i].Create();
			break;
		}
	}
	
	

	//�X�V����
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
		}
		
	}
	for (int i = 0; i < FriendMaxNum; i++)
	{
		whiteBloodCell[i].Update();
	}

	//���Ԍv���p
	g_count++;

	//�`�揈��
	ClearDrawScreen();

	stage.Draw();
	vaccine.Draw();

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].Draw();
	}
	for (int i = 0; i < FriendMaxNum; i++)
	{
		whiteBloodCell[i].Draw();
	}

	DrawGraph(200,0,g_time_handle,true);
	DrawGraph(0,0, g_clock_handle,true);

	ScreenFlip();
	
	if (CheckHitKey(KEY_INPUT_TAB))
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