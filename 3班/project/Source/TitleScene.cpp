#include "TitleScene.h"
#include <DxLib.h>
#include <cassert>
#include "BestTime.h" 

TitleScene::TitleScene()
{
	titleImage = LoadGraph("data/image/背景/newTitle.jpeg");	  // 画像 タイトル画面
		assert(titleImage > 0);
	pushKeyTextImage = LoadGraph("data/image/font/PushKey.png"); //「PUSH ANY KEY」
		assert(pushKeyTextImage > 0);

	startSound = LoadSoundMem("data/sound/GameSE/決定ボタンを押す24.mp3"); // 音 [ANY]ゲーム画面へ
		assert(startSound > 0);
	
	DrawKeyTimer = 0.0f;  // タイマー 
	IsDraw = true;

	changeSceneCountDown = 1.0f;
	IsPushAnyKey = false;
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleImage);
	DeleteGraph(pushKeyTextImage);

	DeleteSoundMem(startSound);
}

void TitleScene::Update()
{
	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	if (KeyUtility::CheckTrigger(KEY_INPUT_ESCAPE))
	{
		SceneManager::Exit();
	}

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
		IsDraw = true;
		IsPushAnyKey = true;
		// サウンド再生
		PlaySoundMem(startSound, DX_PLAYTYPE_BACK);
		
	}
	if (IsPushAnyKey)
	{
		changeSceneCountDown -= Time::DeltaTime();

		if (changeSceneCountDown <= 0)
		{
			SceneManager::ChangeScene("PLAY");
		}
	}
}


void TitleScene::Draw()
{
	// タイトル画像
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // 通常描画
	DrawGraph(0, 0, titleImage, TRUE);

	// [PUSH ANY KEY]表示 
	SetFontSize(50);
	if (IsDraw)
	{
		DrawGraph(0, 0, pushKeyTextImage, TRUE);
	}

	//調整用センタードット
	//DrawString(1280/2, 720/2, ".", GetColor(255, 0, 0), TRUE);
}