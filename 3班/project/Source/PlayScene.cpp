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
	/* //固定表示の文字は無くなる
	nextTextImage = LoadGraph("data/image/font/一画面に統合する前のフォントたち/NEXT.png");			 // 画像「NEXT」
		assert(nextTextImage > 0);
	modeChangeTextImage = LoadGraph("data/image/font/一画面に統合する前のフォントたち/change.png");  // 画像「ChangeC」
		assert(modeChangeTextImage > 0);
	heightTextImage = LoadGraph("data/image/font/一画面に統合する前のフォントたち/Hight.png");		 // 画像「HEIGHT」
		assert(heightTextImage > 0);
	scoreTextImage = LoadGraph("data/image/font/一画面に統合する前のフォントたち/Score.png");		 // 画像「SCORE」
		assert(scoreTextImage > 0);
	timeTextImage = LoadGraph("data/image/font/一画面に統合する前のフォントたち/Time.png");			 // 画像「TIME」
		assert(timeTextImage > 0);
	bestScoreTextImage = LoadGraph("data/image/一画面に統合する前のフォントたち/font/BestScore.png"); // 画像「BEST SCORE」
		assert(bestScoreTextImage > 0);
	bestTimeTextImage = LoadGraph("data/image/一画面に統合する前のフォントたち/font/BestTime.png");	 // 画像「BEST TIME」
		assert(bestTimeTextImage > 0);
	*/

	ladyTextImage = LoadGraph("data/image/XA1/xレディA1.png");	   //画像「レディ…」
		assert(ladyTextImage > 0);
	goTextImage = LoadGraph("data/image/XA1/xゴーA1.png");		   //画像「ゴー！」
		assert(goTextImage > 0);

	tetraModeTextImage = LoadGraph("data/image/font/TETRA.png"); // 画像「TETRA」
		assert(tetraModeTextImage > 0);
	blockModeTextImage = LoadGraph("data/image/font/Block.png"); // 画像「BLOCK」
		assert(blockModeTextImage > 0);
	playModeTextImage = tetraModeTextImage;	// プレイモードのデフォルトは「TETRA」

	tetraModeBGImage = LoadGraph("data/image/XA1/xプレイモードてとら.jpg"); // 画像 TETRAモードのプレイエリア背景画像
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
	// 音声読み込み
	titleBackVoice = LoadSoundMem("data/sound/効果音ラボ/voice/「もうええわ」.mp3");   // 音声 [T]タイトルに戻る
		assert(titleBackVoice > 0);
	changeModeVoice = LoadSoundMem("data/sound/効果音ラボ/voice/「はいは〜い♪」.mp3");// 音声 [C]プレイモード変更
		assert(changeModeVoice > 0);

	g = nullptr;
	f = nullptr;

	playTime = 0.0f;		// プレイ時間

	height = 0.0f;			// 床分の高さ(10)を引く
	bestHeight = 0.0f;		// 死亡時のリザルトで表示

	changeBGheight = 50 /3;
}

PlayScene::~PlayScene()
{
	DeleteGraph(hBGImageI);			 // 画像 プレイシーン 背景1
	DeleteGraph(hBGImageII);		 // 画像 プレイシーン 背景2
	DeleteGraph(hBGImageIII);		 // 画像 プレイシーン 背景3

	DeleteGraph(tetraModeTextImage); // 画像「TETRA」
	DeleteGraph(blockModeTextImage); // 画像「BLOCK」
	DeleteGraph(tetraModeBGImage);   // 画像 TETRAモード背景
	DeleteGraph(blockModeBGImage);   // 画像 BLOCKモード背景
	DeleteGraph(ladyTextImage);		 // 画像「レディ」
	DeleteGraph(goTextImage);		 // 画像「ゴー」

	DeleteGraph(stageTextImage);	 // 画像 [固定表示文字を１枚の画像にまとめた]
	DeleteGraph(nextTextImage);		 // 画像「NEXT」
	DeleteGraph(modeChangeTextImage);// 画像「CHANGE:[C]KEY」
	DeleteGraph(heightTextImage);	 // 画像「HEIGHT」
	DeleteGraph(scoreTextImage);	 // 画像「SCORE」
	DeleteGraph(bestScoreTextImage); // 画像「BEST SCORE」
	DeleteGraph(timeTextImage);		 // 画像「TIME」
	DeleteGraph(bestTimeTextImage);  // 画像「BEST TIME」

	DeleteSoundMem(titleBackVoice);  //音声「CHANGE:[C]KEY」
	DeleteSoundMem(changeModeVoice); //音声「CHANGE:[C]KEY」
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

	// プレイモード切り替え
	if ( (KeyUtility::CheckTrigger(KEY_INPUT_C)) || (input.Buttons[XINPUT_BUTTON_Y]) )
	{
		// ボタンを押し込んだ時だけ入力を取る
		if (!isButtonDown) 
		{
			PlaySoundMem(changeModeVoice, DX_PLAYTYPE_BACK);
			//PlayModeクラスから関数を呼び出す
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
		playModeBGImage = tetraModeBGImage;
	}
	else 				   // ブロックモード
	{
		playModeTextImage = blockModeTextImage;
		playModeBGImage = blockModeBGImage;
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
	////たかさ、タイム、
	//GOALかFINISHを呼び出し
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

	/*
	//「レディ…」→「ゴー！」
	DrawGraph(350, 250, ladyTextImage, TRUE); //「レディ…」
	DrawGraph(430, 230, goTextImage, TRUE);   //「ゴー！」
	*/

	//「NEXT」表示
	//DrawGraph(1025, 50, nextTextImage, TRUE);

	SetFontSize(25);
	//高さ(playerHeight)
	//DrawGraph(1030, 400, heightTextImage, TRUE);
	DrawFormatString(1170, 420, GetColor(255, 255, 255), "%.0f/50", fabs(height));
	
	//スコア(Coin?)
	//DrawGraph(1030, 500, scoreTextImage, TRUE);
	DrawFormatString(1160, 470, GetColor(255, 255, 255), "%d", p->gotCoin);

	//タイム(playTime)
	//DrawGraph(1030, 600, timeTextImage, TRUE);
	DrawFormatString(1135, 525, GetColor(255, 255, 255), "%4.2f", playTime);
	
	SetFontSize(20);
	//ベストスコア(bestScore)
	//DrawGraph(1030, 530, bestScoreTextImage, TRUE);
	DrawFormatString(1155, 605, GetColor(255, 255, 255), "%0d", bestTime->GetBestScore() );
	//ベストタイム(bestTime)
	//DrawGraph(1030, 630, bestTimeTextImage, TRUE);
	DrawFormatString(1135, 635, GetColor(255, 255, 255), "%4.2f", bestTime->GetBestTime() );

	//プレイモード(TETRA/BLOCK)
	DrawGraph(5, 530, playModeTextImage, TRUE);   // playModeTextImageに入れる画像を切り替える
	//「CHANGE：[C] KEY」表示
	//DrawGraph(5, 600, modeChangeTextImage, TRUE);
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

