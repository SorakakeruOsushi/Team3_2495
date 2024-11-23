#include "FinishText.h"
#include "../Library/time.h"

FinishText::FinishText()
{
	timer = 0.0f;
}

FinishText::~FinishText()
{
}

int score = 100;


void FinishText::Update()
{
	//Time::DeltaTime();：秒で測れるためモニター性能に左右されない
	timer += Time::DeltaTime();

	if (timer >= 2.0f)
	{
		//後で一度だけ入力判定にする
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			SceneManager::ChangeScene("TitleScene");
		}
	}

}

void FinishText::Draw()
{

	//現在のフォントサイズ
	int size = GetFontSize();

	//"FINISH!"
	SetFontSize(50);
	DrawString(200, 200, "FINISH! ", GetColor(255, 255, 127)); //(x,y,文字列,色)

	// "SCORE：ｎm"
	// "TIME ：ｎs"
	if (timer >= 1.0f) //１秒超えたらずっと表示
	{
		//(x,y,色,文字列,変わる文字列)   「%d」を置き換える
		//「%6d」 ：６桁用意する　（if文でカンストさせればオーバーしない）
		//「%06d」：６桁用意する　空白を０で埋める
		//「%06d%%」：「ｎ％」表示出来る

		SetFontSize(25);
		DrawFormatString(200, 300, GetColor(255, 255, 255), "SCORE:%06d", score); 
		DrawFormatString(200, 300, GetColor(255, 255, 255), "SCORE:%06d", score);
		
		//到達高さ、クリアタイム（ABC評価）（クリア時のみ）
		//Finish(Dead)とClear(ゴールありなら)で別？
	}

	// "スペースキーで終了"
	if (timer >= 1.5f) //１.５秒超えたらずっと表示
	{
		DrawString(200, 500, "スペースキーを押して終了 ", GetColor(255, 255, 255));
	}

	//元のフォントサイズに戻す
	SetFontSize(size);
}
