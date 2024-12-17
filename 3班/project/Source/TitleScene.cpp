#include "TitleScene.h"
#include <DxLib.h>
#include <cassert>
#include "BestTime.h" 

TitleScene::TitleScene()
{
	titleImage = LoadGraph("data/image/Title.JPG"); // タイトル画面
		assert(titleImage > 0);
	titleLogoImage = LoadGraph("data/image/ロゴ_透過.png"); // タイトルロゴ
		assert(titleLogoImage > 0);
	titleBGImage = LoadGraph("data/image/Back1.png"); // タイトルロゴ
		assert(titleBGImage > 0);
	pushKeyTextImage = LoadGraph("data/image/XA1/xPushAnyKey.png"); //「PUSH ANY KEY」
		assert(pushKeyTextImage > 0);
	
	DrawKeyTimer = 0.0f;  // タイマー 
	IsDraw = true;
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleImage);
	DeleteGraph(titleLogoImage);
	DeleteGraph(titleBGImage);
	DeleteGraph(pushKeyTextImage);
}

void TitleScene::Update()
{
	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	// 表示切替
	DrawKeyTimer += Time::DeltaTime();
	if (DrawKeyTimer >= 0.7f)
	{
		IsDraw = !IsDraw;
		DrawKeyTimer = 0.0f;
	}


	// キー入力なら何でもOK(１回だけ入力)
	if ( (KeyUtility::CheckTriggerAll(DX_CHECKINPUT_KEY)) || (input.Buttons[XINPUT_BUTTON_B]))
	{
		// サウンドが終了するまで待つ 
		//PlaySoundFile(  , DX_PLAYTYPE_NORMAL);
		SceneManager::ChangeScene("PLAY");
	}
	if (KeyUtility::CheckTrigger(KEY_INPUT_ESCAPE))
	{
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	// タイトル画像
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // 通常描画
	//DrawGraph(0, 0, titleImage, TRUE);
	DrawGraph(0, 0, titleBGImage, TRUE);
	DrawGraph(0, 0, titleLogoImage, TRUE);

	// [PUSH ANY KEY]表示 
	SetFontSize(50);
	if (IsDraw)
	{
		// DrawString(340, 500, "ＰＵＳＨ ＡＮＹ ＫＥＹ", GetColor(255, 255, 255), TRUE);
		DrawGraph(270, 500, pushKeyTextImage, TRUE);
	}

	SetFontSize(25);
	DrawString(585, 615, "ＨＥＬＰ", GetColor(255, 255, 255));
	DrawString(560, 650, "ＣＯＮＦＩＧ", GetColor(255, 255, 255));

	//調整用センタードット
	//DrawString(1280/2, 720/2, ".", GetColor(255, 0, 0), TRUE);
}
