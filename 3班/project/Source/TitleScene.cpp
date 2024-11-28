#include "TitleScene.h"
#include <DxLib.h>
#include <cassert>

TitleScene::TitleScene()
{
	titleImage = LoadGraph("data/image/Title.JPG");
		assert(titleImage > 0);
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleImage);
}

void TitleScene::Update()
{

	if (KeyUtility::CheckTrigger(KEY_INPUT_SPACE))
	{
		SceneManager::ChangeScene("PLAY");
	}
	if (KeyUtility::CheckTrigger(KEY_INPUT_ESCAPE))
	{
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	DrawGraph(0, 0, titleImage, TRUE);
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [SPACE]Key To Play", GetColor(255, 255, 255));
	
}
