#include "PlayScene.h"
#include <DxLib.h>
#include <cassert>


PlayScene::PlayScene()
{
	//�\���e�X�g
	pngImage = LoadGraph("data/image/playerA1.png");
	assert(pngImage > 0);//�ǂݍ��߂Ă�?
	jpgImage = LoadGraph("data/image/playerA1.jpg");
	assert(jpgImage > 0);//�ǂݍ��߂Ă�?
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) 
	{
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));


	//�\���e�X�g�p
	DrawGraph(100, 500, pngImage, TRUE);
	DrawGraph(300, 500, jpgImage, TRUE);
}
