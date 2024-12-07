#include "RestartScene.h"
#include "Screen.h"
void RestartScene::Update()
{
	// PlaySceneへ
	SceneManager::ChangeScene("PLAY");
}

void RestartScene::Draw()
{
	//「Now Loading…」的な表示を行う"
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100); //	アルファブレンディング
	SetFontSize(250);
	DrawString(30*10, 200, "RESET", GetColor(255, 255, 255)); //(x,y,文字列,色)
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	 //透過しない
}
