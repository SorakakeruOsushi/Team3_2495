#include "TitleScene.h"
#include <DxLib.h>
#include <cassert>
#include "BestTime.h" 

TitleScene::TitleScene()
{
	titleImage = LoadGraph("data/image/Title.JPG");
		assert(titleImage > 0);

	// 最高得点管理用GameObjectの作成
	Instantiate<BestTime>();
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleImage);
}

void TitleScene::Update()
{
	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	// キー入力なら何でもOK(１回だけ入力)
	if ( (KeyUtility::CheckTriggerAll(DX_CHECKINPUT_KEY)) || (input.Buttons[XINPUT_BUTTON_B]))
	{
		// サウンドが終了するまで待つ 
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
