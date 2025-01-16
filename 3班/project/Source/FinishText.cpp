#include "FinishText.h"
#include "../Library/time.h"
#include <cassert>

FinishText::FinishText()
{
	finishTextImage = LoadGraph("data/image/font/Finish.png");		   // 画像「FINISH」
		assert(finishTextImage > 0);
	gameOverTextImage = LoadGraph("data/image/font/GameOver.png");	   // 画像「GAME OVER」
		assert(gameOverTextImage > 0);
	titleBackKeyTextImage = LoadGraph("data/image/font/PushSpace.png");// 画像「SPACEで終了」
		assert(titleBackKeyTextImage > 0);

	heightTextImage = LoadGraph("data/image/font/一画面に統合する前のフォントたち/Hight.png"); // 画像「HEIGHT」
		assert(heightTextImage > 0);
	scoreTextImage = LoadGraph("data/image/font/一画面に統合する前のフォントたち/Score.png");  // 画像「SCORE」
		assert(scoreTextImage > 0);
	timeTextImage = LoadGraph("data/image/font/一画面に統合する前のフォントたち/Time.png");    // 画像「TIME」
		assert(timeTextImage > 0);

	titleBackSound = LoadSoundMem("data/sound/効果音ラボ/voice/「もうええわ」.mp3"); // 音 タイトルに戻る
		assert(titleBackSound > 0);
	gameOverSound = LoadSoundMem("data/sound/GameSE/ゲームオーバー２.mp3");	 // 音 ゲームオーバーSE
		assert(gameOverSound > 0);
	PlaySoundMem(gameOverSound, DX_PLAYTYPE_BACK); // 悲鳴ボイス再生

	timer = 0.0f;
	alpha = 0.0f;

	DrawKeyTimer = 0.0f;
	IsDraw = false;

	resultHeight =0.0f; // 到達高さ
	resultScore = 0;	// スコア結果 
	resultTime = 0.0f;	// タイム結果
}

FinishText::~FinishText()
{
	DeleteGraph(finishTextImage);
	DeleteGraph(gameOverTextImage);
	DeleteGraph(titleBackKeyTextImage);

	DeleteGraph(heightTextImage);
	DeleteGraph(scoreTextImage);
	DeleteGraph(timeTextImage);

	DeleteSoundMem(titleBackSound);
	DeleteSoundMem(gameOverSound);
}

void FinishText::Update()
{
	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//Time::DeltaTime();：秒で測れるためモニター性能に左右されない
	timer += Time::DeltaTime();

	if (timer >= 1.5f)
	{
		//「タイトルに戻る」表示切替
		DrawKeyTimer += Time::DeltaTime();
		if (DrawKeyTimer >= 0.5f)
		{
			IsDraw = !IsDraw;
			DrawKeyTimer = 0.0f;
		}

		if ( (CheckHitKey(KEY_INPUT_SPACE)) || (input.Buttons[XINPUT_BUTTON_A]) || (input.Buttons[XINPUT_BUTTON_B]) )
		{
			// サウンドが終了するまで待つ 
			PlaySoundMem(titleBackSound, DX_PLAYTYPE_NORMAL);
			SceneManager::ChangeScene("TITLE");
		}
	}

	//alpha値 増加
	if (timer >= 0.3f)
	{
		alpha += 3.0f;
		if (alpha >= 170)
		{
			alpha = 170;
		}
	}
}

void FinishText::Draw()
{
	//「FINISH!」表示
	DrawGraph(0, 0, finishTextImage, TRUE);
	// 暗転
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //透過する
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);   //透過しない

	//「GAME OVER!」表示
	if (timer >= 0.3f) 
	{
		DrawGraph(0, 0, gameOverTextImage, TRUE);
	}
	SetFontSize(80);
	if (timer >= 0.5f)
	{
		// 到達高さ表示
		DrawGraph(326, 300, heightTextImage, TRUE);
		DrawFormatString(615, 300, GetColor(255, 255, 255), "%3.0f", fabs(resultHeight));
	}
	if (timer >= 0.75f)
	{
		// スコア表示
		DrawGraph(340, 400, scoreTextImage, TRUE);
		DrawFormatString(615, 400, GetColor(255, 255, 255), "%3.0d", resultScore);
	}
	if (timer >= 1.0f)
	{
		// タイム表示
		DrawGraph(421, 500, timeTextImage, TRUE);
		DrawFormatString(615, 500, GetColor(255, 255, 255), "%6.2f", resultTime);
	}

	// "スペースキーで終了"
	if (IsDraw)
	{
		//「スペースキーを押して終了」表示
		DrawGraph(450, 600, titleBackKeyTextImage, TRUE);
		SetFontSize(25);
		DrawString(450, 650, "test[0]でリトライ", GetColor(255, 0, 0), TRUE);
	}

}
