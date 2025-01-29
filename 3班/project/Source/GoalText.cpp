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
	
	heightTextImage = LoadGraph("data/image/font/一画面に統合する前のフォントたち/Hight.png"); // 画像「HEIGHT」
		assert(heightTextImage > 0);
	scoreTextImage = LoadGraph("data/image/font/一画面に統合する前のフォントたち/Score.png");  // 画像「SCORE」
		assert(scoreTextImage > 0);
	timeTextImage = LoadGraph("data/image/font/一画面に統合する前のフォントたち/Time.png");    // 画像「TIME」
		assert(timeTextImage > 0);

	titleBackKeyTextImage = LoadGraph("data/image/font/PushSpace.png"); // 画像「TITLEに戻る」
		assert(titleBackKeyTextImage > 0);

	titleBackSound = LoadSoundMem("data/sound/GameSE/ボタン１.mp3");
		assert(titleBackSound > 0);
	//goalSound = LoadSoundMem("data/sound/効果音ラボ/voice/「ぱんぱかぱーん！」.mp3");
	goalSound = LoadSoundMem("data/sound/GameSE/魔王魂ゴールSE.mp3");
	//goalSound = LoadSoundMem("data/sound/GameSE/ゴール.mp3");
		assert(goalSound > 0);
	PlaySoundMem(goalSound, DX_PLAYTYPE_BACK); // ゴールボイス再生

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

	DeleteGraph(heightTextImage);
	DeleteGraph(scoreTextImage);
	DeleteGraph(timeTextImage);

	DeleteSoundMem(titleBackSound);
	DeleteSoundMem(goalSound);
}

void GoalText::Update()
{
	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//Time::DeltaTime();：秒で測れるためモニター性能に左右されない
	timer += Time::DeltaTime();

	if (timer >= 7.0f)
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
			// サウンドが終了するまで待つ 
			PlaySoundMem(titleBackSound, DX_PLAYTYPE_NORMAL);
			SceneManager::ChangeScene("TITLE");
		}
	}

	//alpha値 増加
	if (timer >= 0.5f)
	{
		alpha += 2.5f;
		if (alpha >= 255)
		{
			alpha = 255;
		}
	}
}

void GoalText::Draw()
{
	//「FINISH!」表示
	DrawGraph(0, 0, finishTextImage, TRUE);
	// ゴール画像 表示
	if (timer >= 0.3f)
	{
		// リザルト画面背景
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //	アルファブレンディング
		DrawGraph(0, 0, goalBGImage, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	 // 透過しない
	}

	if (timer >= 3.5f)
	{
		// 暗転
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50); // 透過する
		DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);   // 透過しない
	}

	//「GAME CLEAR!」表示
	if (timer >= 4.0f)
	{
		DrawGraph(0, -175, gameClearTextImage, TRUE);
	}
	SetFontSize(80);
	if (timer >= 5.0f)
	{
		// 高さ(固定表示)
		DrawGraph(326, 300, heightTextImage, TRUE);
		DrawString(615, 300, " 50/50", GetColor(255, 255, 255)); // ハリボテ
	}
	if (timer >= 5.5f)
	{
		// スコア表示
		DrawGraph(340, 400, scoreTextImage, TRUE);
		DrawFormatString(615, 400, GetColor(255, 255, 255)," %.0f", resultScore);
		if (IsNewBestScore)
		{
			DrawGraph(900, 400, newRecordTextImage, TRUE);
		}

	}
	if (timer >= 6.0f)
	{
		// タイム表示
		DrawGraph(421, 500, timeTextImage, TRUE);
		DrawFormatString(615, 500, GetColor(255, 255, 255), " %.2f", resultTime);
		if (IsNewBestTime)
		{
			DrawGraph(900, 500, newRecordTextImage, TRUE);
		}
	}

	// "スペースキーで終了"
	if (IsDraw)
	{
		//「スペースキーを押して終了」表示
		DrawGraph(0, 0, titleBackKeyTextImage, TRUE);
	}

	//調整用センタードット
	//DrawString(1280/2, 720/2, ".", GetColor(255, 0, 0), TRUE);
}
