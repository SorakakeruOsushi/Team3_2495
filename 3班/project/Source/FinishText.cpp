#include "FinishText.h"
#include "../Library/time.h"
#include <cassert>

FinishText::FinishText()
{
	finishTextImage = LoadGraph("data/image/font/Finish.png");						  // 画像「FINISH」
		assert(finishTextImage > 0);
	gameOverTextImage = LoadGraph("data/image/font/GameOver.png");					  // 画像「GAME OVER」
		assert(gameOverTextImage > 0);
	titleBackKeyTextImage = LoadGraph("data/image/XA1/xスペースキーを押して終了.png");// 画像「SPACEで終了」
		assert(titleBackKeyTextImage > 0);

	gameOverVoice = LoadSoundMem("data/sound/効果音ラボ/voice/「ひゃーっ！」.mp3");	  // 音声「(悲鳴)」
		assert(gameOverVoice > 0);
	PlaySoundMem(gameOverVoice, DX_PLAYTYPE_BACK); // 悲鳴ボイス再生

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
	DeleteSoundMem(gameOverVoice);
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
			SceneManager::ChangeScene("TITLE");
		}
	}

	//alpha値 増加
	if (timer >= 0.3f)
	{
		alpha += 3.0f;
		if (alpha >= 125)
		{
			alpha = 125;
		}
	}
}

void FinishText::Draw()
{
	//「FINISH!」表示
	DrawGraph(340, 280, finishTextImage, TRUE);
	// 暗転
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //透過する
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //透過しない

	//「GAME OVER!」表示
	if (timer >= 0.3f) 
	{
		DrawGraph(255, 260, gameOverTextImage, TRUE);
	}
	SetFontSize(30);
	if (timer >= 0.5f)
	{
		// 到達高さ表示
		DrawFormatString(500, 450, GetColor(255, 255, 255), "たかさ%3.0f", fabs(resultHeight));
		// スコア表示
		DrawFormatString(500, 480, GetColor(255, 255, 255), "すこあ%3.0d", resultScore);
	}
	if (timer >= 1.0f)
	{
		// タイム表示
		DrawFormatString(500, 500, GetColor(255, 255, 255), "たいむ%4.2f", resultTime);
	}

	// "スペースキーで終了"
	if (IsDraw)
	{
		//「スペースキーを押して終了」表示
		DrawGraph(450, 600, titleBackKeyTextImage, TRUE);
	}
}
