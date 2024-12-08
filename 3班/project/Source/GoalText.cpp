#include "GoalText.h"
#include "../Library/time.h"
#include <cassert>

GoalText::GoalText()
{
	goalVoice = LoadSoundMem("data/sound/効果音ラボ/voice/「ぱんぱかぱーん！」.mp3");
		assert(goalVoice > 0);
	PlaySoundMem(goalVoice, DX_PLAYTYPE_BACK); // ゴールボイス

	goalBGImage = LoadGraph("data/image/goalBGX.png");
		assert(goalBGImage > 0);

	timer = 0.0f;
	alpha = 0.0f;
}

GoalText::~GoalText()
{
	DeleteSoundMem(goalVoice);
	DeleteGraph(goalBGImage);
}

void GoalText::Update()
{
	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//Time::DeltaTime();：秒で測れるためモニター性能に左右されない
	timer += Time::DeltaTime();

	if (timer >= 6.0f)
	{
		if ((CheckHitKey(KEY_INPUT_SPACE)) || (input.Buttons[XINPUT_BUTTON_A]) || (input.Buttons[XINPUT_BUTTON_B]))
		{
			SceneManager::ChangeScene("TITLE");
		}
	}

	if (timer >= 0.3f)
	{
		alpha += 1.5f;
		if (alpha >= 255)
		{
			alpha = 255;
		}
	}
}

void GoalText::Draw()
{
	/*
	//「ゴール！」的な表示を行う"
	SetFontSize(100);
	DrawString(310, 200, "おめでとう", GetColor(255, 255, 127)); //(x,y,文字列,色)

	if (timer >= 0.3f) //１秒超えたらずっと表示
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


}
