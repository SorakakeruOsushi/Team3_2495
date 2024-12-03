#include "TitleScene.h"
#include <DxLib.h>
#include <cassert>
#include "BestTime.h" 

TitleScene::TitleScene()
{
	titleImage = LoadGraph("data/image/Title.JPG");
		assert(titleImage > 0);

	// �ō����_�Ǘ��pGameObject�̍쐬
	Instantiate<BestTime>();
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleImage);
}

void TitleScene::Update()
{

	if (CheckHitKeyAll(DX_CHECKINPUT_KEY))
	{
		// �T�E���h���I������܂ő҂� 
		//PlaySoundFile(  , DX_PLAYTYPE_NORMAL);
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

	SetFontSize(50);
	DrawString(500, 600, "PUSH ANY KEY", GetColor(255, 255, 255));
	
}
