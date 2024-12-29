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

	ladyTextImage = LoadGraph("data/image/XA1/xレディA1.png");	   //画像「レディ…」
		assert(ladyTextImage > 0);
	goTextImage = LoadGraph("data/image/XA1/xゴーA1.png");		   //画像「ゴー！」
		assert(goTextImage > 0);
	ladyGoTextImage = ladyTextImage;		// LadyGoのデフォルトは「Lady」
	
	tetraModeTextImage = LoadGraph("data/image/font/TETRA.png"); // 画像「TETRA」
		assert(tetraModeTextImage > 0);
	blockModeTextImage = LoadGraph("data/image/font/Block.png"); // 画像「BLOCK」
		assert(blockModeTextImage > 0);
	playModeTextImage = tetraModeTextImage;	// プレイモードのデフォルトは「TETRA」

	tetraModeBGImage = LoadGraph("data/image/XA1/xプレイモードてとら.jpg");   // 画像 TETRAモードのプレイエリア背景画像
		assert(tetraModeBGImage > 0);
	blockModeBGImage = LoadGraph("data/image/XA1/xプレイモードぶろっく.jpg"); // 画像 BLOCKモードのプレイエリア背景画像
		assert(blockModeBGImage > 0);
	playModeBGImage = tetraModeBGImage;		// プレイモードのデフォルトは「TETRA」
	// 画像 背景1,2,3
	hBGImageI = LoadGraph("data/image/Back1.png");
		assert(hBGImageI > 0);
	hBGImageII = LoadGraph("data/image/Back2.png");
		assert(hBGImageII > 0);
	hBGImageIII = LoadGraph("data/image/Back3.png");
		assert(hBGImageIII > 0);
	gameBGImage = hBGImageI; // デフォルトの背景画像
	// 画像 ポーズ画面
	pauseImage = LoadGraph("data/image/xPause.png"); // 画像 ポーズ画面
		assert(pauseImage > 0);
	//「RESET!」
	//resetTextImage = LoadGraph("data/image/XA1/xRESET.png"); // 画像「RESET」
	//	assert(resetTextImage > 0);

	// 音声読み込み
	titleBackSound = LoadSoundMem("data/sound/効果音ラボ/voice/「もうええわ」.mp3");   // 音 [T]タイトルに戻る
		assert(titleBackSound > 0);
	tetraModeSound = LoadSoundMem("data/sound/効果音ラボ/voice/「もうええわ」.mp3");   // 音 [C]テトラモード
		assert(tetraModeSound > 0);
	blockModeSound = LoadSoundMem("data/sound/効果音ラボ/voice/「もうええわ」.mp3");   // 音 [C]ブロックモード
		assert(blockModeSound > 0);
	startSound = LoadSoundMem("data/sound/効果音ラボ/voice/「もうええわ」.mp3");   // 音 ゲーム開始
		assert(startSound > 0);
	pauseSound = LoadSoundMem("data/sound/効果音ラボ/voice/「もうええわ」.mp3");   // 音 [Tab]ポーズ
		assert(pauseSound > 0);
	//resetSound = LoadSoundMem("data/sound/効果音ラボ/voice/「もうええわ」.mp3");   // 音 [0]リセット
	//	assert(resetSound > 0);

	g = nullptr;
	f = nullptr;

	playTime = 0.0f;		// プレイ時間

	//IsReset = false;
	startCountDown = 5.0f;

	height = 0.0f;			// 床分の高さ(10)を引く
	bestHeight = 0.0f;		// 死亡時のリザルトで表示

	changeBGheight = 50 / 3;
}

PlayScene::~PlayScene()
{
	DeleteGraph(hBGImageI);			 // 画像 プレイシーン 背景1
	DeleteGraph(hBGImageII);		 // 画像 プレイシーン 背景2
	DeleteGraph(hBGImageIII);		 // 画像 プレイシーン 背景3

	DeleteGraph(stageTextImage);	 // 画像 [固定表示文字を１枚の画像にまとめた]

	DeleteGraph(tetraModeTextImage); // 画像「TETRA」
	DeleteGraph(blockModeTextImage); // 画像「BLOCK」
	DeleteGraph(tetraModeBGImage);   // 画像 TETRAモード背景
	DeleteGraph(blockModeBGImage);   // 画像 BLOCKモード背景
	DeleteGraph(ladyTextImage);		 // 画像「レディ」
	DeleteGraph(goTextImage);		 // 画像「ゴー」

	DeleteGraph(pauseImage);		 // 画像 ポーズ画面
	//DeleteGraph(resetTextImage);	 // 画像「RESET」

	DeleteSoundMem(titleBackSound); // 音「CHANGE:[C]KEY」
	DeleteSoundMem(tetraModeSound); // 音 [C]テトラモード変更時
	DeleteSoundMem(blockModeSound); // 音 [C]ブロックモード変更時
	DeleteSoundMem(startSound);		// 音 ゲーム開始
	DeleteSoundMem(pauseSound);		// 音 [Tab]ポーズ
	//DeleteSoundMem(resetSound);		// 音 [0]リセット
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

	//ゲーム開始
	if (KeyUtility::CheckTrigger(KEY_INPUT_2));
	{
		//PlaySoundMem(startSound, DX_PLAYTYPE_BACK);
		pm->IsGameStart = true;
	}


	if (!pm->IsGameStart)
	{
		return;
	}
	//[0]リスタート
	if (KeyUtility::CheckTrigger(KEY_INPUT_0))
	{
		//IsReset = true;
		//PlaySoundMem(resetSound, DX_PLAYTYPE_BACK); // SE再生
		//１フレームだけ"RESTARTシーン"に行き、"PLAYシーン"に戻ってくる
		SceneManager::ChangeScene("RESTART");
	}
	//[Tab]ポーズ&操作ヘルプ
	if (!pm->IsGamePause) // ポーズ中じゃない
	{
		if ((KeyUtility::CheckTrigger(KEY_INPUT_TAB)) || (input.Buttons[XINPUT_BUTTON_START]))
		{
			// ボタンを押し込んだ時だけ入力を取る
			if (!isButtonDown)
			{
				PlaySoundMem(pauseSound, DX_PLAYTYPE_BACK);
				pm->IsGamePause = true; // ゲーム中断
			}
			isButtonDown = true;
		}
		else
		{
			isButtonDown = false;
		}
		if (pm->IsGamePause)
		{
			return;
		}
	}
	 else // ポーズ中
	{
		// [Tab] ／ [START]または[A]
		if ( (KeyUtility::CheckTrigger(KEY_INPUT_TAB)) || (input.Buttons[XINPUT_BUTTON_START]) || (input.Buttons[XINPUT_BUTTON_A]))
		{
			// ボタンを押し込んだ時だけ入力を取る
			if (!isButtonDown)
			{
				//PlaySoundMem(pauseSound, DX_PLAYTYPE_BACK); // 違う音?
				pm->IsGamePause = false; // ゲーム再開
			}
			isButtonDown = true;
		}
		else
		{
			isButtonDown = false;
		}
		if (pm->IsGamePause)
		{
			return;
		}
	}

	//[1]セル表示切り替え
	if (KeyUtility::CheckTrigger(KEY_INPUT_1))
	{
		s->cellBG = !s->cellBG;
	}
	//[C]プレイモード切り替え
	if ((KeyUtility::CheckTrigger(KEY_INPUT_C)) || (input.Buttons[XINPUT_BUTTON_Y]))
	{
		// ボタンを押し込んだ時だけ入力を取る
		if (!isButtonDown)
		{
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
		//PlaySoundMem(tetraModeSound, DX_PLAYTYPE_BACK);
		playModeTextImage = tetraModeTextImage;
		playModeBGImage = tetraModeBGImage;
	}
	else 				   // ブロックモード
	{
		//PlaySoundMem(blockModeSound, DX_PLAYTYPE_BACK);
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

	//背景の表示切り替え
	if ( (height >= changeBGheight * 0) && (height < changeBGheight * 1) )
	{
		gameBGImage = hBGImageI;
	}
	if ((height >= changeBGheight * 1) && (height < changeBGheight * 2))
	{
		gameBGImage = hBGImageII;
	}
	if ((height >= changeBGheight * 2) && (height < changeBGheight * 3))
	{
		gameBGImage = hBGImageIII;
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
	// プレイエリア外のの背景
	DrawGraph(0, 0, gameBGImage, TRUE); // 洞窟の背景

	// プレイモード背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawGraph(30 * 8, 0, playModeBGImage, TRUE); // TETRA/BLOCK
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(0, 0, stageTextImage, TRUE);    // 固定表示の文字

	//「レディ…」→「ゴー！」
	DrawGraph(350, 250, ladyGoTextImage, TRUE); //「レディ…」「ゴー！」
	

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
	DrawGraph(5, 530, playModeTextImage, TRUE);   // playModeTextImageに入れる画像を切り替える

	//「RESET!」表示
	//if (IsReset) 
	{
		//DrawGraph(30 * 8.5, 200, resetTextImage, TRUE);
	}


	//ポーズ画面　(表示順バグ)
	if (pm->IsGamePause)
	{
		// 画面を暗くする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200); //透過する
		DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //透過しない
		// ポーズ画面
		DrawGraph(0, 0, pauseImage, TRUE);
	}

	SetFontSize(100);
	//DrawFormatString(300, 300, GetColor(255, 255, 255), "%0.0f", startCountDown);
	DrawString(300, 300, "テスト中、[2]でゲーム開始", GetColor(255, 255, 0), TRUE);
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

