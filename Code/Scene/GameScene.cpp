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
	SetBackgroundColor(255, 233, 207);		//�w�i�F�ύX

	vaccine.Initialize();
	timer.Initialize();
	InitializeEnemies(virus);
	InitializeFriends(whiteBloodCell);
	
	//�`��̓ǂݍ���
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
	//��������
	if (timer.GetCurrentCounter() == 0)	//��������
	{
		CreateEnemies(virus);
		CrateFriends(whiteBloodCell,5);
	}
	
	if (timer.GetCurrentCounter() % 960 == 0 && timer.GetCurrentCounter() != 0)
	{
		CrateFriends(whiteBloodCell,1);		//16�b���Ƃɐ�������
	}
	
	//�ȉ��������Ƃ��ꂢ�ɂ��� -------------------------------------------------------------------------
	//Enemy�APlayer�Ɣ������̓����蔻��
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

	//Player��Enemy�̓�����
	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].ToPlayer(&vaccine);
	}
	
	//�X�V����
	timer.Update();	//���Ԃ̍X�V
	vaccine.Update();	//�v���C���[�̍X�V

	//�������̍X�V����
	ChangeStateFriend(whiteBloodCell);
	UpdateFriends(whiteBloodCell);
	//EraseFriend(whiteBloodCell);
	
	if (whiteBloodCell[SearchTiredFriend(whiteBloodCell)].GetCurrentState() == true)
	{
		UpdateEnemies(virus, &whiteBloodCell[SearchTiredFriend(whiteBloodCell)]);
	}
	else	//������^�[�Q�b�g�̕ύX
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
	
	//�`�揈��
	ClearDrawScreen();

	stage.Draw();		//�X�e�[�W

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		virus[i].Draw();	//�E�C���X
	}
	for (int i = 0; i < FriendMaxNum; i++)
	{
		whiteBloodCell[i].Draw();	//������
	}

	vaccine.DrawSpaceKey(&whiteBloodCell[SearchTiredFriend(whiteBloodCell)]);	//�X�y�[�X�L�[

	vaccine.Draw();		//���N�`��

	timer.Draw();	//����

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