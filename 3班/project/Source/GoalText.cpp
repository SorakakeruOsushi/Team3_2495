#include "GoalText.h"
#include "../Library/time.h"
#include <cassert>

GoalText::GoalText()
{
	goalBGImage = LoadGraph("data/image/Goal.JPG");						  // 画像 ゴール背景画像
		assert(goalBGImage > 0);
	finishTextImage = LoadGraph("data/image/font/Finish.png");		      // 画像「FINISH」
		assert(finishTextImage > 0);
	gameClearTextImage = LoadGraph("data/image/font/Clear.png");	      // 画像「GAME CLEAR」
		assert(gameClearTextImage > 0);
	newRecordTextImage = LoadGraph("data/image/font/NewRecord.png");	  // 画像「NEW RECORD!」
		assert(newRecordTextImage > 0);
	thanksTextImage = LoadGraph("data/image/XA1/xThankYouForPlaying.png");// 画像「プレイしてくれてありがとナス！」
		assert(thanksTextImage > 0);
	titleBackKeyTextImage = LoadGraph("data/image/XA1/xスペースキーを押して終了.png"); // 画像「TITLEに戻る」
		assert(titleBackKeyTextImage > 0);

	goalVoice = LoadSoundMem("data/sound/効果音ラボ/voice/「ぱんぱかぱーん！」.mp3");
		assert(goalVoice > 0);
	PlaySoundMem(goalVoice, DX_PLAYTYPE_BACK); // ゴールボイス再生

	timer = 0.0f;
	alpha = 0.0f;

	DrawKeyTimer = 0.0f;
	IsDraw = false;

	IsNewBestScore = false;
	IsNewBestTime = false;

	resultScore = 0;   // スコア結果
	resultTime = 0.0f; // タイム結果
}

GoalText::~GoalText()
{
	DeleteGraph(goalBGImage);
	DeleteGraph(finishTextImage);
	DeleteGraph(gameClearTextImage);
	DeleteGraph(newRecordTextImage);
	DeleteGraph(titleBackKeyTextImage);
	DeleteGraph(thanksTextImage);
	DeleteSoundMem(goalVoice);
}

void GoalText::Update()
{
	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//Time::DeltaTime();：秒で測れるためモニター性能に左右されない
	timer += Time::DeltaTime();

	if (timer >= 6.0f)
	{
		//「タイトルに戻る」表示切替
		DrawKeyTimer += Time::DeltaTime();
		if (DrawKeyTimer >= 0.5f)
		{
			IsDraw = !IsDraw;
			DrawKeyTimer = 0.0f;
		}

		if ((CheckHitKey(KEY_INPUT_SPACE)) || (input.Buttons[XINPUT_BUTTON_A]) || (input.Buttons[XINPUT_BUTTON_B]))
		{
			SceneManager::ChangeScene("TITLE");
		}
	}

	//alpha値 増加
	if (timer >= 0.3f)
	{
		alpha += 1.0f;
		if (alpha >= 255)
		{
			alpha = 255;
		}
	}
}

void GoalText::Draw()
{
	//「FINISH!」表示
	DrawGraph(340, 280, finishTextImage, TRUE);
	// ゴール画像 表示
	if (timer >= 0.3f)
	{
		// リザルト画面背景
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //	アルファブレンディング
		DrawGraph(0, 0, goalBGImage, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	 //透過しない
	}

	//「GAME CLEAR!」表示
	if (timer >= 3.0f)
	{
		DrawGraph(255, 160, gameClearTextImage, TRUE);
	}
	SetFontSize(30);
	if (timer >= 4.0f)
	{
		//高さ(固定表示)
		DrawString(500, 300, "50/50", GetColor(255, 255, 255)); // ハリボテ
	}
	if (timer >= 4.5f)
	{
		// スコア表示
		DrawFormatString(500, 350, GetColor(255, 255, 255), "%3.0d", resultScore);
		if (IsNewBestScore)
		{
			DrawGraph(600, 350, newRecordTextImage, TRUE);
		}

	}
	//タイム
	if (timer >= 5.0f)
	{
		// タイム表示
		DrawFormatString(500, 400, GetColor(255, 255, 255), "%4.2f", resultTime);
		if (IsNewBestTime)
		{
			DrawGraph(600, 400, newRecordTextImage, TRUE);
		}
	}

	if (timer >= 5.3f)
	{
		//「Thank You For Playing!」表示
		DrawGraph(275, 500, thanksTextImage, TRUE);
	}

	// "スペースキーで終了"
	if (IsDraw)
	{
		//「スペースキーを押して終了」表示
		DrawGraph(450, 600, titleBackKeyTextImage, TRUE);
	}
}
