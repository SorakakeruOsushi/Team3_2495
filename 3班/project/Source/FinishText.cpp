#include "FinishText.h"
#include "../Library/time.h"

FinishText::FinishText()
{
	timer = 0.0f;
	
}

FinishText::~FinishText()
{
}

void FinishText::Update()
{
	//Time::DeltaTime();：秒で測れるためモニター性能に左右されない
	timer += Time::DeltaTime();

	if (timer >= 2.0f)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			SceneManager::ChangeScene("TITLE");
		}
	}

}

void FinishText::Draw()
{

	//現在のフォントサイズ
	int size = GetFontSize();

	//"FINISH!"
	SetFontSize(100);
	DrawString(200, 200, "TETRA DEAD", GetColor(255, 100, 100)); //(x,y,文字列,色)

	if (timer >= 1.0f) //１秒超えたらずっと表示
	{
		//(x,y,色,文字列,変わる文字列)   「%d」を置き換える
		//「%6d」 ：６桁用意する　（if文でカンストさせればオーバーしない）
		//「%06d」：６桁用意する　空白を０で埋める
		//「%06d%%」：「ｎ％」表示出来る

		//到達した高さ、時間を表示
		SetFontSize(25);
		//高さ(playerHeight)
		DrawFormatString(200, 300, GetColor(255, 255, 255), "SCORE:%3.0f", fabs(resultHeight));
		DrawFormatString(200, 400, GetColor(255, 255, 255), "TIME:%4.2f", resultTime);
	}

	// "スペースキーで終了"
	if (timer >= 1.5f) //１.５秒超えたらずっと表示
	{
		DrawString(200, 500, "スペースキーを押して終了 ", GetColor(255, 255, 255));
	}

	//元のフォントサイズに戻す
	SetFontSize(size);
}
