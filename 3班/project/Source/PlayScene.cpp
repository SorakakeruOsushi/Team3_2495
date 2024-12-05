#include <DxLib.h>
#include "../Library/sceneManager.h"
#include "PlayScene.h"
#include "Player.h"
#include <cassert>
#include "Block.h"
#include "time.h"
#include "../Library/Utility.h"

PlayScene::PlayScene()
{
	s = Instantiate<Stage>();
	p = FindGameObject<Player>();

	Instantiate<Block>();

	titleBackVoice = LoadSoundMem("data/sound/効果音ラボ/voice/「もうええわ」.mp3");
		assert(titleBackVoice > 0);
	changeModeVoice = LoadSoundMem("data/sound/効果音ラボ/voice/「はいは～い♪」.mp3");
		assert(changeModeVoice > 0);

	/*
	// BGMのループ再生
	gameBGM = LoadSoundMem("data/sound/効果音ラボ/水のしたたる洞窟.mp3");
		assert(gameBGM > 0);
	PlaySoundMem(gameBGM, DX_PLAYTYPE_LOOP);
	*/

	g = nullptr;
	f = nullptr;

	playMode = 0; //プレイモード(プレイヤー０/ブロック１)

	playTime = 0.0f;		//プレイ時間

	height = 0.0f;			//床文の高さ(10)を引く
	bestHeight = 0.0f;

	// 最高得点管理用GameObjectの取得 
	bestTime = FindGameObject<BestTime>();
		assert(bestTime != nullptr);

	//IsPause = false; // ポーズ
}

PlayScene::~PlayScene()
{
	DeleteSoundMem(titleBackVoice);
	DeleteSoundMem(changeModeVoice);
	DeleteSoundMem(gameBGM);
}

void PlayScene::Update()
{
	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	// タイトルへ戻る（隠し機能）
	if (CheckHitKey(KEY_INPUT_T))
	{
		// サウンドが終了するまで待つ 
		PlaySoundMem(titleBackVoice, DX_PLAYTYPE_NORMAL);
		SceneManager::ChangeScene("TITLE");
	}

	//[Tab]ポーズ(願望)
	if (KeyUtility::CheckTrigger(KEY_INPUT_TAB))
	{
		//IsPause = !IsPause;
	}
	//[0]リスタート(願望)
	if (KeyUtility::CheckTrigger(KEY_INPUT_0))
	{
		//レスターとシーン
		//SceneManager::ChangeScene("PLAY");
	}
	//[1]セル表示(願望)
	if (KeyUtility::CheckTrigger(KEY_INPUT_1))
	{
		
	}
	
	
	if (!p->finished && !p->goaled)
	{
		//タイマー
		playTime += Time::DeltaTime();
		//playTimeのカンスト(9999)
		if (playTime >= 9999)
		{
			playTime = 9999;
		}

		//高さ(height)
		if ((s != nullptr) && (s->p != nullptr))
		{
			height = s->p->playerHeight / 30;
		}
	}

	// プレイモード切り替え
	if ( (KeyUtility::CheckTrigger(KEY_INPUT_C)) || (input.Buttons[XINPUT_BUTTON_Y]) )
	{
		//PlayModeクラスから関数を呼び出す
		//ここに

		PlaySoundMem(changeModeVoice, DX_PLAYTYPE_BACK);
		playMode = (playMode + 1) % 2; // ０か１
	}
	
	//GOALかFINISHを呼び出し
	if (p->goaled && g == nullptr)
	{
		g = FindGameObject<GoalText>();
		g->resultTime = playTime;
		g->resultHeight = bestHeight;
		// 最高得点確認 
		CheckBestTime();
		return;
	}
	if (p->finished && f == nullptr)
	{
		f = Instantiate<FinishText>();
		f->resultTime = playTime;
		f->resultHeight = bestHeight;
		return;
	}

}

void PlayScene::Draw()
{
	SetFontSize(40);
	DrawString(1035, 50, "N E X T", GetColor(255, 255, 255));

	//(x,y,色,文字列,変わる文字列)   「%d」を置き換える
	//「%6d」 ：６桁用意する　（if文でカンストさせればオーバーしない）
	//「%06d」：６桁用意する　空白を０で埋める
	//「%06d%%」：「ｎ％」表示出来る
	//デフォルトでは右詰なので、左詰にしたいときは桁数指定のまえにマイナスをつけなければならない。

	SetFontSize(25);
	//高さ(playerHeight)
	DrawFormatString(1030, 400, GetColor(255, 255, 255), "HEIGHT:%.0f/50", fabs(height));
	//スコア(highScore + Coin?)
	DrawFormatString(1030, 500, GetColor(255, 255, 255), "SCORE:%0.0f", 0);
	//タイム(playTime)
	DrawFormatString(1030, 600, GetColor(255, 255, 255), "TIME:%4.2f", playTime);
	
	SetFontSize(15);
	//ベストスコア(bestScore)
	DrawFormatString(1030, 530, GetColor(255, 255, 255), "BEST SCORE:%0.0f", 0);
	//ベストタイム(bestTime)
	DrawFormatString(1030, 630, GetColor(255, 255, 255), "BEST TIME:%4.2f", bestTime->GetBestTime() );

	//プレイモード(TETRA/BLOCK)
	SetFontSize(60);
	DrawFormatString(25, 530, GetColor(255, 255, 255), "%5s", playMode == 0 ? "TETRA" : "BLOCK");
	SetFontSize(20);
	//モード変更
	DrawString(20, 600, "CHANGE：[C] KEY", GetColor(255, 255, 255));
}

void PlayScene::CheckBestTime()
{
	// 時間を短縮更新する 
	if (playTime < bestTime->GetBestTime())
	{
		bestTime->SetBestTime(playTime);
	}
}
