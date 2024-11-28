#include <DxLib.h>
#include "../Library/sceneManager.h"
#include "PlayScene.h"
#include "Player.h"
#include "Block.h"
#include "time.h"

PlayScene::PlayScene()
{
	s = Instantiate<Stage>();
	p = FindGameObject<Player>();

	Instantiate<Block>();

	f = nullptr;

	playTime = 0.0f;		//プレイ時間

	bestTime = 0.0f;		//ベストクリア時間

	score = 0.0f;			//床文の高さ(10)を引く
	highScore = 0.0f;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	
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
			score = s->p->playerHeight;
		}
		//ハイスコア
		if (highScore <= score/30)
		{
			highScore = score/30;
		}
	}
	

	// タイトルへ戻る（隠し機能）
	if (CheckHitKey(KEY_INPUT_T)) 
	{
		SceneManager::ChangeScene("TITLE");
	}

	//GOALかFINISHを呼び出し
	if (p->goaled)
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
	DrawString(1000, 100, "N E X T", GetColor(255, 255, 255));

	//(x,y,色,文字列,変わる文字列)   「%d」を置き換える
	//「%6d」 ：６桁用意する　（if文でカンストさせればオーバーしない）
	//「%06d」：６桁用意する　空白を０で埋める
	//「%06d%%」：「ｎ％」表示出来る
	//デフォルトでは右詰なので、左詰にしたいときは桁数指定のまえにマイナスをつけなければならない。
	/*
	指定例	出力結果
	printf("[%15s]", "I am a boy.");	[I am a boy.]
	printf("[%8.3f]", 123.45678);		[123.456]
	printf("[%5d]", 1);				[     1]
	*/

	SetFontSize(25);
	//レベル(stageLevel)
	DrawFormatString(1000, 400, GetColor(255, 255, 255), "LEVEL:%02d", 1);

	//高さ(playerHeight)
	DrawFormatString(1000, 450, GetColor(255, 255, 255), "SCORE:%3.0f", fabs(highScore));
	
	//タイマー(playTime)
	DrawFormatString(1000, 500, GetColor(255, 255, 255), "TIME:%4.2f", playTime);

	//現在のモードを表示(仮) PLAYER/BLOCK
	DrawString(1000, 600, "MODE：PLAYER", GetColor(255, 255, 255));

	SetFontSize(15);
	//モード変更
	DrawString(1000, 650, "CHANGE：push [C] key", GetColor(255, 255, 255));

	//現在のLEVELとか
}
