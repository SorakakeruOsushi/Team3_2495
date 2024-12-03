#include "GoalText.h"
#include "../Library/time.h"
#include <cassert>

GoalText::GoalText()
{
	goalVoice = LoadSoundMem("data/sound/効果音ラボ/voice/「ぱんぱかぱーん！」.mp3");
		assert(goalVoice > 0);
	PlaySoundMem(goalVoice, DX_PLAYTYPE_BACK); // ゴールボイス

	timer = 0.0f;
}

GoalText::~GoalText()
{
}

void GoalText::Update()
{
	//Time::DeltaTime();：秒で測れるためモニター性能に左右されない
	timer += Time::DeltaTime();

	if (timer >= 2.5f)
	{
		if (KeyUtility::CheckTrigger(KEY_INPUT_SPACE))
		{
			SceneManager::ChangeScene("TITLE");
		}
	}
}

void GoalText::Draw()
{

	//現在のフォントサイズ
	int size = GetFontSize();

	//"Goal!"
	SetFontSize(100);
	DrawString(200, 200, "CLEAR! ", GetColor(255, 255, 127)); //(x,y,文字列,色)

	if (timer >= 1.0f) //１秒超えたらずっと表示
	{
		//(x,y,色,文字列,変わる文字列)   「%d」を置き換える
		//「%6d」 ：６桁用意する　（if文でカンストさせればオーバーしない）
		//「%06d」：６桁用意する　空白を０で埋める
		//「%06d%%」：「ｎ％」表示出来る

		//(一応)高さ、時間、評価を表示
		SetFontSize(25);
		DrawFormatString(200, 300, GetColor(255, 255, 255), "SCORE:%3.0f", fabs(resultHeight));
		DrawFormatString(200, 400, GetColor(255, 255, 255), "TIME:%4.2f", resultTime);
		if (timer >= 1.5f)
		{
			SetFontSize(40);
			//DrawFormatString(200, 500, GetColor(255, 255, 255), "評価:%d",A～E  );
		}
	}

	// "スペースキーで終了"
	if (timer >= 2.0f)
	{
		DrawString(200, 600, "スペースキーを押して終了 ", GetColor(255, 255, 255));
	}

	//元のフォントサイズに戻す
	SetFontSize(size);
}
