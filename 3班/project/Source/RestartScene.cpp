#include "RestartScene.h"
#include "Screen.h"
#include <cassert>

RestartScene::RestartScene()
{
	
	resetTextImage = LoadGraph("data/image/XA1/xRESET.png"); //�uRESET!�v
		assert(resetTextImage > 0);
	//resetSE = LoadSoundMem("data/sound/���ʉ����{/�W�����v.mp3");  // ���Z�b�g�T�E���h
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
	// PlayScene��
	SceneManager::ChangeScene("PLAY");
}

void RestartScene::Draw()
{
	// [RESET!]�\��
	DrawGraph(30 * 8.5, 200, resetTextImage, TRUE);
	/* 
	SetFontSize(60);
	DrawString(420, 340, "�q�d�r�d�s!", GetColor(255, 255, 255), TRUE);
	*/

	/*
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	*/
}
