#include "TitleScene.h"
#include <DxLib.h>
#include <cassert>
#include "BestTime.h" 

TitleScene::TitleScene()
{
	titleImage = LoadGraph("data/image/Title.JPG");			  // 画像 タイトル画面
		assert(titleImage > 0);
	titleLogoImage = LoadGraph("data/image/ロゴ_透過.png");   // 画像 タイトルロゴ
		assert(titleLogoImage > 0);
	titleBGImage = LoadGraph("data/image/Back1.png");		  // 画像 タイトル画面背景
		assert(titleBGImage > 0);
	pushKeyTextImage = LoadGraph("data/image/font/Push.png"); //「PUSH ANY KEY」
		assert(pushKeyTextImage > 0);

	startSound = LoadSoundMem("data/sound/効果音ラボ/voice/「もうええわ」.mp3");   // 音 [T]タイトルに戻る
		assert(startSound > 0);
	
	DrawKeyTimer = 0.0f;  // タイマー 
	IsDraw = true;
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleImage);
	DeleteGraph(titleLogoImage);
	DeleteGraph(titleBGImage);
	DeleteGraph(pushKeyTextImage);

	DeleteSoundMem(startSound);
}

void TitleScene::Update()
{
	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	// 表示切替
	DrawKeyTimer += Time::DeltaTime();
	if (DrawKeyTimer >= 0.7f)
	{
		IsDraw = !IsDraw;
		DrawKeyTimer = 0.0f;
	}


	// キー入力なら何でもOK(１回だけ入力)
	if ( (KeyUtility::CheckTriggerAll(DX_CHECKINPUT_KEY)) || (input.Buttons[XINPUT_BUTTON_B]))
	{
		// サウンドが終了するまで待つ 
		PlaySoundMem(startSound, DX_PLAYTYPE_NORMAL);
		SceneManager::ChangeScene("PLAY");
	}
	if (KeyUtility::CheckTrigger(KEY_INPUT_ESCAPE))
	{
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	// タイトル画像
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // 通常描画
	//DrawGraph(0, 0, titleImage, TRUE);
	DrawGraph(0, 0, titleBGImage, TRUE);
	DrawGraph(0, 0, titleLogoImage, TRUE);

	// [PUSH ANY KEY]表示 
	SetFontSize(50);
	if (IsDraw)
	{
		DrawGraph(330, 500, pushKeyTextImage, TRUE);
	}

	//調整用センタードット
	DrawString(1280/2, 720/2, ".", GetColor(255, 0, 0), TRUE);
}
