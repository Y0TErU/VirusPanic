#include "Scene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ClearScene.h"
#include "OverScene.h"

SceneType g_CurrentSceneType = title;
SceneStep g_CurrentSceneStep = init;

int g_nextScene;

void ExecuteScene()
{
	switch (g_CurrentSceneType)
	{
	case title:
		ExecuteTitleScene();
		break;
	case game:
		ExecuteGameScene();
		break;
	case clear:
		ExecuteClearScene();
		break;
	case over:
		ExecuteOverScene();
		break;
	}
}