#include "GoalText.h"
#include "../Library/time.h"
#include <cassert>

GoalText::GoalText()
{
	goalBGImage = LoadGraph("data/image/Goal.JPG");						  // 画像 ゴール背景画像
		assert(goalBGImage > 0);
	finishTextImage = LoadGraph("data/image/XA1/xFinishA1.png");		  // 画像「FINISH」文字画像
		assert(finishTextImage > 0);
	gameClearTextImage = LoadGraph("data/image/XA1/xGAME_CLEAR.png");	  // 画像「GAME CLEAR」文字画像
		assert(gameClearTextImage > 0);
	thanksTextImage = LoadGraph("data/image/XA1/xThankYouForPlaying.png");// 画像「GAME CLEAR」文字画像
		assert(thanksTextImage > 0);
	bannerImage = LoadGraph("data/image/XA1/xバナー1.png");
		assert(bannerImage > 0);
	titleBackKeyTextImage = LoadGraph("data/image/XA1/xスペースキーを押して終了.png");
		assert(titleBackKeyTextImage > 0);

	goalVoice = LoadSoundMem("data/sound/効果音ラボ/voice/「ぱんぱかぱーん！」.mp3");
		assert(goalVoice > 0);
	PlaySoundMem(goalVoice, DX_PLAYTYPE_BACK); // ゴールボイス

	timer = 0.0f;
	alpha = 0.0f;
	bannerSlide = -1280.0f;
}

GoalText::~GoalText()
{
	DeleteGraph(goalBGImage);
	DeleteGraph(finishTextImage);
	DeleteGraph(gameClearTextImage);
	DeleteGraph(bannerImage);
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

	if (timer >= 5.5f)
	{
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
	//帯スライド
	if (timer >= 5.0f)
	{
		bannerSlide += 30;
		if (bannerSlide >= 1280.0f)
		{
			bannerSlide = 1280.0f;
		}
	}
}

void GoalText::Draw()
{
	/*
	//「ゴール！」的な表示を行う"
	SetFontSize(100);
	DrawString(310, 200, "おめでとう", GetColor(255, 255, 127)); //(x,y,文字列,色)

	if (timer >= 0.3f)
	{
		//(x,y,色,文字列,変わる文字列)   「%d」を置き換える
		//「%6d」 ：６桁用意する　（if文でカンストさせればオーバーしない）
		//「%06d」：６桁用意する　空白を０で埋める
		//「%06d%%」：「ｎ％」表示出来る

		// リザルト画面背景
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //	アルファブレンディング
		DrawGraph(0, 0, goalBGImage, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	 //透過しない

		DrawString(310, 200, "おめでとう", GetColor(255, 255, 127)); //(x,y,文字列,色)
	}

	SetFontSize(50);
	if (timer >= 4.5f)
	{
		DrawFormatString(500, 350, GetColor(255, 255, 255), "SCORE:%3.0f", fabs(resultHeight));//スコアに変わる、高さは死のみ
	}
	if (timer >= 5.0f)
	{
		DrawFormatString(500, 450, GetColor(255, 255, 255), "TIME:%4.2f", resultTime);
	}
	// "スペースキーで終了"
	if (timer >= 5.5f)
	{
		DrawString(300, 600, "スペースキーを押して終了 ", GetColor(255, 255, 255));
	}
	*/

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
		// スコア表示
		DrawFormatString(500, 350, GetColor(255, 255, 255), "SCORE:%3.0f", fabs(resultHeight));//スコアに変わる、高さは死のみ
	}
	if (timer >= 4.5f)
	{
		// タイム表示
		DrawFormatString(500, 400, GetColor(255, 255, 255), "TIME:%4.2f", resultTime);
	}

	if (timer >= 4.8f)
	{
		//「Thank You For Playing!」表示
		DrawGraph(275, 500, thanksTextImage, TRUE);
	}

	// "スペースキーで終了"
	if (timer >= 5.0f)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawRectGraph(0, 600, 0, 0, bannerSlide, 50, bannerImage, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (timer >= 5.5f)
		{
			//「スペースキーを押して終了」表示
			DrawGraph(450, 600, titleBackKeyTextImage, TRUE);
		}
	}
}
