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

	gameBGM = LoadSoundMem("data/sound/効果音ラボ/水のしたたる洞窟.mp3");
		assert(gameBGM > 0);
	//BGM
	PlaySoundMem(gameBGM, DX_PLAYTYPE_LOOP);

	/*
	h10Voice = LoadSoundMem("data/sound/効果音ラボ/voice/「10（じゅう↓）」.mp3");
		assert(h10Voice > 0);
	*/

	g = nullptr;
	f = nullptr;

	playTime = 0.0f;		//プレイ時間
	bestTime = 0.0f;		//ベストクリア時間

	score = 0.0f;			//床文の高さ(10)を引く
	highScore = 0.0f;
}

PlayScene::~PlayScene()
{
	DeleteSoundMem(titleBackVoice);
	DeleteSoundMem(changeModeVoice);
	DeleteSoundMem(gameBGM);

	//DeleteSoundMem(h10Voice);
}

void PlayScene::Update()
{
	// タイトルへ戻る（隠し機能）
	if (CheckHitKey(KEY_INPUT_T))
	{
		// サウンドが終了するまで待つ 
		PlaySoundMem(titleBackVoice, DX_PLAYTYPE_NORMAL);
		SceneManager::ChangeScene("TITLE");
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

		//スコア
		if ((s != nullptr) && (s->p != nullptr))
		{
			score = s->p->playerHeight / 30;
		}
		/*
		//ハイスコア
		if (highScore <= score)
		{
			highScore = score;
		}
		if (highScore >= 10.0f)
		{
			PlaySoundMem(h10Voice, DX_PLAYTYPE_BACK);
		}
		*/
	}

	// プレイモード切り替え
	if (KeyUtility::CheckTrigger(KEY_INPUT_C))
	{
		PlaySoundMem(changeModeVoice, DX_PLAYTYPE_BACK);
	}
	
	//GOALかFINISHを呼び出し
	if (p->goaled && g == nullptr)
	{
		g = FindGameObject<GoalText>();
		g->resultTime = playTime;
		g->resultHeight = highScore;
		return;
	}
	if (p->finished && f == nullptr)
	{
		f = Instantiate<FinishText>();
		f->resultTime = playTime;
		f->resultHeight = highScore;
		return;
	}

}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));

	SetFontSize(40);
	DrawString(1035, 50, "N E X T", GetColor(255, 255, 255));

	//(x,y,色,文字列,変わる文字列)   「%d」を置き換える
	//「%6d」 ：６桁用意する　（if文でカンストさせればオーバーしない）
	//「%06d」：６桁用意する　空白を０で埋める
	//「%06d%%」：「ｎ％」表示出来る
	//デフォルトでは右詰なので、左詰にしたいときは桁数指定のまえにマイナスをつけなければならない。

	SetFontSize(25);
	//高さ(playerHeight)
	DrawFormatString(1030, 300, GetColor(255, 255, 255), "HEIGHT:%2.0f/50", fabs(score));
	//スコア(highScore + Coin?)
	DrawFormatString(1030, 400, GetColor(255, 255, 255), "SCORE:%0.0f", 0);
	//タイム(playTime)
	DrawFormatString(1030, 500, GetColor(255, 255, 255), "TIME:%4.2f", playTime);
	
	SetFontSize(15);
	//ベストスコア(bestScore)
	DrawFormatString(1030, 430, GetColor(255, 255, 255), "BEST SCORE:%0.0f", 0);
	//ベストタイム(bestTime)
	DrawFormatString(1030, 530, GetColor(255, 255, 255), "BEST TIME:%4.2f", 0.00);

	//プレイモード(TETRA/BLOCK)
	SetFontSize(60);
	DrawString(20, 530, "TETRA", GetColor(255, 255, 255));
	//DrawFormatString(20, 530, GetColor(255, 255, 255), "%5s", playMode);
	SetFontSize(20);
	//モード変更
	DrawString(20, 600, "CHANGE：[C] KEY", GetColor(255, 255, 255));

	//現在のLEVELとか
}
