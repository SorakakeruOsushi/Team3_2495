#include "FinishText.h"
#include "../Library/time.h"
#include <cassert>

FinishText::FinishText()
{
	finishTextImage = LoadGraph("data/image/font/Finish.png");						  // 画像「FINISH」
		assert(finishTextImage > 0);
	gameOverTextImage = LoadGraph("data/image/font/GameOver.png");					  // 画像「GAME OVER」
		assert(gameOverTextImage > 0);
	bannerImage = LoadGraph("data/image/XA1/xバナー1.png");
		assert(bannerImage > 0);
	titleBackKeyTextImage = LoadGraph("data/image/XA1/xスペースキーを押して終了.png");// 画像「SPACEで終了」
		assert(titleBackKeyTextImage > 0);

	gameOverVoice = LoadSoundMem("data/sound/効果音ラボ/voice/「ひゃーっ！」.mp3");	  // 音声「(悲鳴)」
		assert(gameOverVoice > 0);
	PlaySoundMem(gameOverVoice, DX_PLAYTYPE_BACK); // 悲鳴ボイス再生

	timer = 0.0f;
	alpha = 0.0f;
	bannerSlide = -1280.0f;
}

FinishText::~FinishText()
{
	DeleteGraph(finishTextImage);
	DeleteGraph(gameOverTextImage);
	DeleteGraph(bannerImage);
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
	//帯スライド
	if (timer >= 1.5f)
	{
		bannerSlide +=30;
		if (bannerSlide >= 1280.0f)
		{
			bannerSlide = 1280.0f;
		}
	}
}

void FinishText::Draw()
{
	/*
	//「ゲームオーバー！」的な表示を行う"
	SetFontSize(100);
	DrawString(310, 200, "ざんね～ん", GetColor(255, 255, 127)); //(x,y,文字列,色)

	
	if (timer >= 0.3f) //１秒超えたらずっと表示
	{
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
	*/

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
		// スコア表示
		DrawFormatString(500, 450, GetColor(255, 255, 255), "SCORE:%3.0f", fabs(resultHeight));//スコアに変わる、高さは死のみ
	}
	if (timer >= 1.0f)
	{
		// タイム表示
		DrawFormatString(500, 500, GetColor(255, 255, 255), "TIME:%4.2f", resultTime);
	}

	// "スペースキーで終了"
	if (timer >= 1.5f)
	{
		/* //ボックス
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255); //透過する
		DrawBox(0, 600, bannerSlide, 650, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //透過しない
		*/
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		//DrawRectGraph(0, 600, 0,0, bannerSlide,50, bannerImage, TRUE);
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (timer >= 2.0f)
		{
			//「スペースキーを押して終了」表示
			DrawGraph(450, 600, titleBackKeyTextImage, TRUE);
		}
	}
}
