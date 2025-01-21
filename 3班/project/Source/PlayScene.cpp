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
	pm = Instantiate<PlayMode>();
	s = Instantiate<Stage>();
	
	// コンストラクタ
	p = FindGameObject<Player>();
		assert(pm != nullptr);
	pm = FindGameObject<PlayMode>();
		assert(pm != nullptr);
	bestTime = FindGameObject<BestTime>(); // 最高得点管理用GameObjectの取得 
		assert(bestTime != nullptr);

	Instantiate<Block>();
	// 画像読み込み
	stageTextImage = LoadGraph("data/image/font/StageFont.png"); // 画像 [固定表示文字を１枚の画像にまとめた]
		assert(stageTextImage > 0);
	resetTextImage = LoadGraph("data/image/font/Reset.png");	 // 画像「RESET[0]KEY」
		assert(resetTextImage > 0);

	readyTextImage = LoadGraph("data/image/font/READY.png");	   //画像「レディ…」
		assert(readyTextImage > 0);
	goTextImage = LoadGraph("data/image/font/GO.png");		   //画像「ゴー！」
		assert(goTextImage > 0);
	readyGoTextImage = readyTextImage;		// LadyGoのデフォルトは「Lady」
	
	tetraModeTextImage = LoadGraph("data/image/font/TETRA.png"); // 画像「TETRA」
		assert(tetraModeTextImage > 0);
	blockModeTextImage = LoadGraph("data/image/font/Block.png"); // 画像「BLOCK」
		assert(blockModeTextImage > 0);
	playModeTextImage = tetraModeTextImage;	// プレイモードのデフォルトは「TETRA」

	blockModeBGImage = LoadGraph("data/image/XA1/xプレイモードぶろっく.jpg"); // 画像 BLOCKモードのプレイエリア背景画像
		assert(blockModeBGImage > 0);
	playModeBGImage = NULL;	// プレイモードのデフォルトは「TETRA」

	gameBGImage = LoadGraph("data/image/背景/LongBack.jpeg");    // 画像 背景
		assert(gameBGImage > 0);
	cellMaxImage = LoadGraph("data/image/背景/cell.png");		 // 画像 マス目大きい
		assert(cellMaxImage > 0);
	
	// 音声読み込み
	titleBackSound = LoadSoundMem("data/sound/GameSE/スタートボタン４.mp3"); // 音 [T]タイトルに戻る
		assert(titleBackSound > 0);
	startSound = LoadSoundMem("data/sound/GameSE/ホイッスル・単発02.mp3");   // 音 ゲーム開始
		assert(startSound > 0);
	resetSound = LoadSoundMem("data/sound/GameSE/リセット音.mp3");			 // 音 [0]リセット
		assert(resetSound > 0);
	modeChangeSound = LoadSoundMem("data/sound/GameSE/ボタン１.mp3");		 // 音 [C]モード変更
		assert(modeChangeSound > 0);

	g = nullptr;
	f = nullptr;

	playTime = 0.0f;		// プレイ時間

	startCountDown = 5.0f;

	height = 0.0f;			// 床分の高さ(10)を引く
	bestHeight = 0.0f;		// 死亡時のリザルトで表示
}

PlayScene::~PlayScene()
{
	DeleteGraph(gameBGImage);		 // 画像 プレイシーン背景
	DeleteGraph(cellMaxImage);       // 画像 セルマックス

	DeleteGraph(stageTextImage);	 // 画像 [固定表示文字を１枚の画像にまとめた]

	DeleteGraph(tetraModeTextImage); // 画像「TETRA」
	DeleteGraph(blockModeTextImage); // 画像「BLOCK」
	DeleteGraph(blockModeBGImage);   // 画像 BLOCKモード背景
	DeleteGraph(readyTextImage);	 // 画像「レディ」
	DeleteGraph(goTextImage);		 // 画像「ゴー」

	DeleteSoundMem(titleBackSound); // 音「CHANGE:[C]KEY」
	DeleteSoundMem(startSound);		// 音 ゲーム開始
	DeleteSoundMem(resetSound);		// 音 [0]リセット
	DeleteSoundMem(modeChangeSound);// 音 [C]モード変更時
}



void PlayScene::Update()
{
	//パッド用関数(毎フレーム呼び出す)
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//[T]タイトルへ戻る（隠し機能）
	if (CheckHitKey(KEY_INPUT_T))
	{
		// サウンドが終了するまで待つ 
		PlaySoundMem(titleBackSound, DX_PLAYTYPE_NORMAL);
		SceneManager::ChangeScene("TITLE");
	}

	startCountDown -= Time::DeltaTime();
	
	//ゲーム開始
	if ((startCountDown <= 1.0f) && (startCountDown > 0.75f))
	{
		readyGoTextImage = NULL;
	}
	if ( (startCountDown <= 0.75f) && (startCountDown > 0.0f) )
	{
		readyGoTextImage = goTextImage;
	}
	if (startCountDown <= 0.0f && !pm->IsGameStart)
	{
		readyGoTextImage = NULL;
		PlaySoundMem(startSound, DX_PLAYTYPE_BACK);
		pm->IsGameStart = true;
	}


	if (!pm->IsGameStart)
	{
		return;
	}
	//[0]リスタート
	if (KeyUtility::CheckTrigger(KEY_INPUT_0))
	{
		PlaySoundMem(resetSound, DX_PLAYTYPE_NORMAL); // リセットSE再生
		//１フレームだけ"RESTARTシーン"に行き、"PLAYシーン"に戻ってくる
		SceneManager::ChangeScene("RESTART");
	}

	//[C]プレイモード切り替え
	if ((KeyUtility::CheckTrigger(KEY_INPUT_C)) || (input.Buttons[XINPUT_BUTTON_Y]))
	{
		// ボタンを押し込んだ時だけ入力を取る
		if (!isButtonDown)
		{
			PlaySoundMem(modeChangeSound, DX_PLAYTYPE_BACK);
			pm->changeMode();
		}
		isButtonDown = true;
	}
	else
	{
		isButtonDown = false;
	}

	if (pm->playMode == 0) // テトラモード
	{
		playModeTextImage = tetraModeTextImage;
		playModeBGImage = NULL;
	}
	else 				   // ブロックモード
	{
		playModeTextImage = blockModeTextImage;
		playModeBGImage = blockModeBGImage;
	}
	
	
	if (!p->finished && !p->goaled)
	{
		//高さ(height)
		if ((s != nullptr) && (s->p != nullptr))
		{
			height = s->p->playerHeight / 30;
		}
		//最高到達点(bestHeight)
		if(height > bestHeight)
		{
			bestHeight = height;
		}
		//タイマー
		playTime += Time::DeltaTime();
		//playTimeのカンスト(9999)
		if (playTime >= 9999)
		{
			playTime = 9999;
		}
	}

	//GOALかFINISHでリザルトを確定
	if (p->goaled && g == nullptr)
	{
		g = FindGameObject<GoalText>();
		//高さは50固定
		// スコア
		g->resultScore = p->gotCoin;
		// プレイ時間（クリア時間）
		g->resultTime = playTime;

		// ベストタイム確認 
		CheckBestTime();
		// ベストスコア確認 
		CheckBestScore();
		return;
	}
	if (p->finished && f == nullptr)
	{
		f = Instantiate<FinishText>();
		// 最高到達点
		f->resultHeight = bestHeight;
		// スコア
		f->resultScore = p->gotCoin;
		// プレイ時間
		f->resultTime = playTime;
		return;
	}

}

void PlayScene::Draw()
{
	// 固定背景
	DrawGraph(0, -1440 - s->scroll, gameBGImage, TRUE);

	// プレイモード背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawGraph(30 * 8, 0, playModeBGImage, TRUE); // TETRA/BLOCK
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (pm->playMode == 1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50); //	アルファブレンディング
		DrawGraph(CHIP_SIZE * 8, -1440 - s->scroll, cellMaxImage, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 透過しない
	}

	//固定表示文字画像
	DrawGraph(0, 0, stageTextImage, TRUE);    // 固定表示の文字
	//固定表示文字画像
	DrawGraph(0, 0, resetTextImage, TRUE);    //「RESET[0]KEY」

	//「レディ…」→「ゴー！」
	DrawGraph(0, 0, readyGoTextImage, TRUE); //「レディ…」「ゴー！」
	

	SetFontSize(25);
	//高さ(playerHeight)
	DrawFormatString(1170, 420, GetColor(255, 255, 255), "%.0f/50", fabs(height));
	
	//スコア(Coin?)
	DrawFormatString(1160, 470, GetColor(255, 255, 255), "%d", p->gotCoin);

	//タイム(playTime)
	DrawFormatString(1135, 525, GetColor(255, 255, 255), "%4.2f", playTime);
	
	SetFontSize(20);
	//ベストスコア(bestScore)
	DrawFormatString(1155, 605, GetColor(255, 255, 255), "%0d", bestTime->GetBestScore() );
	//ベストタイム(bestTime)
	DrawFormatString(1135, 635, GetColor(255, 255, 255), "%4.2f", bestTime->GetBestTime() );

	//プレイモード(TETRA/BLOCK)
	DrawGraph(0, 0, playModeTextImage, TRUE);   // playModeTextImageに入れる画像を切り替える

}

// ベストスコアを更新
void PlayScene::CheckBestScore()
{
	if (p->gotCoin > bestTime->GetBestScore())
	{
		bestTime->SetBestScore(p->gotCoin);
		g->IsNewBestScore = true;
	}
}

void PlayScene::CheckBestTime()
{
	// ベストタイムを更新する 
	if (playTime < bestTime->GetBestTime())
	{
		bestTime->SetBestTime(playTime);
		g->IsNewBestTime = true;
	}
}

