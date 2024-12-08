#include "RestartScene.h"
#include "Screen.h"
#include <cassert>

RestartScene::RestartScene()
{
	resetTextImage = LoadGraph("data/image/XA1/xRESET.png");
		assert(resetTextImage > 0);
}
RestartScene::~RestartScene()
{
	DeleteGraph(resetTextImage);
}
void RestartScene::Update()
{
	// PlayScene‚Ö
	SceneManager::ChangeScene("PLAY");
}

void RestartScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(30*8.5,200, resetTextImage, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
