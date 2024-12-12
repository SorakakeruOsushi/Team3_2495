#include "TitleScene.h"
#include <DxLib.h>
#include <cassert>
#include "BestTime.h" 

TitleScene::TitleScene()
{
	titleImage = LoadGraph("data/image/Title.JPG");
		assert(titleImage > 0);
	pushKeyTextImage = LoadGraph("data/image/XA1/xPushAnyKey.png");
		assert(pushKeyTextImage > 0);
	
	DrawKeyTimer = 0.0f;  // タイマー 
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleImage);
	DeleteGraph(pushKeyTextImage);
}

void TitleScene::Update()
{
	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);


	//

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
	// タイトル画面 
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // 通常描画 
	DrawGraph(0, 0, titleImage, TRUE);

	// [PUSH ANY KEY]表示 
	DrawGraph(300, 500, pushKeyTextImage, TRUE);
}
