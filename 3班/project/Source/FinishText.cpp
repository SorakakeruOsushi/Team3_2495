#include "FinishText.h"
#include "../Library/time.h"
#include <cassert>

FinishText::FinishText()
{
	gameOverVoice = LoadSoundMem("data/sound/効果音ラボ/voice/「ひゃーっ！」.mp3");
		assert(gameOverVoice > 0);
	PlaySoundMem(gameOverVoice, DX_PLAYTYPE_BACK); // 悲鳴ボイス

	timer = 0.0f;
	alpha = 0.0f;
}

FinishText::~FinishText()
{
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
		if ( (CheckHitKey(KEY_INPUT_SPACE)) || (input.Buttons[XINPUT_BUTTON_A]) || (input.Buttons[XINPUT_BUTTON_B]) )
		{
			SceneManager::ChangeScene("TITLE");
		}
	}

	if (timer >= 0.3f)
	{
		alpha += 3.0f;
		if (alpha >= 150)
		{
			alpha = 150;
		}
	}
}

void FinishText::Draw()
{
	//「ゲームオーバー！」的な表示を行う"
	SetFontSize(100);
	DrawString(310, 200, "ざんね～ん", GetColor(255, 255, 127)); //(x,y,文字列,色)

	
	if (timer >= 0.3f) //１秒超えたらずっと表示
	{
		//(x,y,色,文字列,変わる文字列)   「%d」を置き換える
		//「%6d」 ：６桁用意する　（if文でカンストさせればオーバーしない）
		//「%06d」：６桁用意する　空白を０で埋める
		//「%06d%%」：「ｎ％」表示出来る

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //透過する
	DrawBox(0, 0, 1280, 720, GetColor(0,0,0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //透過しない

	DrawString(310, 200, "ざんね～ん", GetColor(255, 255, 127));
	}

	SetFontSize(50);
	if (timer >= 0.5f)
	{
		DrawFormatString(450, 350, GetColor(255, 255, 255), "SCORE:%3.0f", fabs(resultHeight));//スコアに変わる、高さは死のみ
	}
	if (timer >= 1.0f)
	{
		DrawFormatString(450, 450, GetColor(255, 255, 255), "TIME:%4.2f", resultTime);
	}
	// "スペースキーで終了"
	if (timer >= 1.5f)
	{
		DrawString(300, 600, "スペースキーを押して終了 ", GetColor(255, 255, 255));
	}
}
