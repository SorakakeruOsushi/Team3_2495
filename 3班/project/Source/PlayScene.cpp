#include <DxLib.h>
#include <cassert>
#include "../Library/sceneManager.h"
#include "PlayScene.h"
#include "Player.h"
#include "Block.h"
#include "time.h"
#include "../Library/Utility.h"

PlayScene::PlayScene()
{
	s = Instantiate<Stage>();
	p = FindGameObject<Player>();
	/*
	pm = FindGameObject<PlayMode>();
		assert(pm != nullptr);
	*/
	bestTime = FindGameObject<BestTime>(); // 最高得点管理用GameObjectの取得 
		assert(bestTime != nullptr);

	Instantiate<Block>();
	// 画像読み込み
	nextTextImage = LoadGraph("data/image/XA1/xNEXT.png");
		assert(nextTextImage > 0);
	modeChangeTextImage = LoadGraph("data/image/XA1/xChangeCKey.png");
		assert(modeChangeTextImage > 0);
	tetraModeTextImage = LoadGraph("data/image/XA1/xTETRA.png");
		assert(tetraModeTextImage > 0);
	blockModeTextImage = LoadGraph("data/image/XA1/xBLOCK.png");
		assert(blockModeTextImage > 0);
	// 音声読み込み
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

	playTime = 0.0f;		//プレイ時間

	height = 0.0f;			//床文の高さ(10)を引く
	bestHeight = 0.0f;
}

PlayScene::~PlayScene()
{
	DeleteGraph(nextTextImage);
	DeleteGraph(modeChangeTextImage);
	DeleteSoundMem(titleBackVoice);
	DeleteSoundMem(changeModeVoice);
	DeleteSoundMem(gameBGM);
}

void PlayScene::Update()
{
	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//[T]タイトルへ戻る（隠し機能）
	if (CheckHitKey(KEY_INPUT_T))
	{
		// サウンドが終了するまで待つ 
		PlaySoundMem(titleBackVoice, DX_PLAYTYPE_NORMAL);
		SceneManager::ChangeScene("TITLE");
	}
	//[Tab]ポーズ&操作ヘルプ
	if (KeyUtility::CheckTrigger(KEY_INPUT_TAB))
	{
		// COMING SOON
	}
	//[0]リスタート
	if (KeyUtility::CheckTrigger(KEY_INPUT_0))
	{
		//１フレームだけ"RESTARTシーン"に行き、"PLAYシーン"に戻ってくる
		SceneManager::ChangeScene("RESTART");
	}
	//[1]セル表示切り替え
	if (KeyUtility::CheckTrigger(KEY_INPUT_1))
	{
		s->cellBG = !s->cellBG;
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
		PlaySoundMem(changeModeVoice, DX_PLAYTYPE_BACK);
		//PlayModeクラスから関数を呼び出す
		pm->changeMode();
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
	//「NEXT」表示
	DrawGraph(1025, 50, nextTextImage, TRUE);

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
	//SetFontSize(60);
	//DrawFormatString(25, 530, GetColor(255, 255, 255), "%5s", pm->playMode == 0 ? "TETRA" : "BLOCK");
	DrawGraph(5, 530, tetraModeTextImage, TRUE); //playModeImageに入れる画像を切り替える?
	//「CHANGE：[C] KEY」表示
	DrawGraph(5, 600, modeChangeTextImage, TRUE);
}

void PlayScene::CheckBestTime()
{
	// 時間を短縮更新する 
	if (playTime < bestTime->GetBestTime())
	{
		bestTime->SetBestTime(playTime);
	}
}
