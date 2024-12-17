#include "RestartScene.h"
#include "Screen.h"
#include <cassert>

RestartScene::RestartScene()
{
	
	resetTextImage = LoadGraph("data/image/XA1/xRESET.png"); //「RESET!」
		assert(resetTextImage > 0);
	//resetSE = LoadSoundMem("data/sound/効果音ラボ/ジャンプ.mp3");  // リセットサウンド
	//	assert(resetSE > 0);
	//PlaySoundMem(resetSE, DX_PLAYTYPE_BACK);
}
RestartScene::~RestartScene()
{
	DeleteGraph(resetTextImage);
	//DeleteSoundMem(resetSE);
}
void RestartScene::Update()
{
	// PlaySceneへ
	SceneManager::ChangeScene("PLAY");
}

void RestartScene::Draw()
{
	// [RESET!]表示
	DrawGraph(30 * 8.5, 200, resetTextImage, TRUE);
	/* 
	SetFontSize(60);
	DrawString(420, 340, "ＲＥＳＥＴ!", GetColor(255, 255, 255), TRUE);
	*/

	/*
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	*/
}
