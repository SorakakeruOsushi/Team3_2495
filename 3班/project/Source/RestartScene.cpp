#include "RestartScene.h"
#include "Screen.h"
void RestartScene::Update()
{
	// PlayScene��
	SceneManager::ChangeScene("PLAY");
}

void RestartScene::Draw()
{
	//�uNow Loading�c�v�I�ȕ\�����s��"
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100); //	�A���t�@�u�����f�B���O
	SetFontSize(250);
	DrawString(30*10, 200, "RESET", GetColor(255, 255, 255)); //(x,y,������,�F)
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	 //���߂��Ȃ�
}
