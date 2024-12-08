#include "TitleScene.h"
#include <DxLib.h>
#include <cassert>
#include "BestTime.h" 

TitleScene::TitleScene()
{
	titleImage = LoadGraph("data/image/Title.JPG");
		assert(titleImage > 0);
	pushKeyTextImage = LoadGraph("data/image/X/XpushAnyKey.png");
		assert(pushKeyTextImage > 0);

	// 最高得点管理用GameObjectの作成
	Instantiate<BestTime>();

	alpha = 0;    // [PUSH SPACE KEY]のアルファ値 
	ofset = (int)((float)MAX_ALPHA / DRAW_KEY_WAIT);
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


	// アルファ値の計算 
	alpha += (int)(ofset * Time::DeltaTime());
	// 前フレームからの経過時間を取得 
	DrawKeyTimer += Time::DeltaTime();
	// 一定時間(DRAW_KEY_WAIT)経過したら、アルファ値の加算・減算を切りかえる 
	if (DrawKeyTimer >= DRAW_KEY_WAIT)
	{
		ofset = -ofset;
		DrawKeyTimer = 0.0f;
	}

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

	// [PUSH SPACE KEY] 
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); // アルファブレンディング 
	DrawGraph(300, 500, pushKeyTextImage, TRUE);
}
