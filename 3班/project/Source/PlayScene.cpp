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
	nextTextImage = LoadGraph("data/image/XA1/xNEXT.png");   // 画像「NEXT」
		assert(nextTextImage > 0);
	modeChangeTextImage = LoadGraph("data/image/XA1/xChangeCKey.png"); // 画像「ChangeC」
		assert(modeChangeTextImage > 0);

	modeChangeTextImage = LoadGraph("data/image/XA1/xChangeCKey.png"); // 画像「ChangeC」
		assert(modeChangeTextImage > 0);

	ladyTextImage = LoadGraph("data/image/XA1/xレディA1.png"); //画像「レディ…」
		assert(ladyTextImage > 0);
	goTextImage = LoadGraph("data/image/XA1/xゴーA1.png");	 //画像「ゴー！」
		assert(goTextImage > 0);
	// 無くてもいい?
	playModeTextImage = LoadGraph("data/image/XA1/xTETRA.png");	 // プレイモードのデフォルトは「TETRA」
		assert(modeChangeTextImage > 0);
	playModeBGImage = LoadGraph("data/image/X/XmodeBGtetra.png");// プレイモードのデフォルトは「TETRA」
		assert(modeChangeTextImage > 0);

	// 画像 背景1,2,3
	hBGImageI = LoadGraph("data/image/Back1.png");
		assert(hBGImageI > 0);
	hBGImageII = LoadGraph("data/image/Back2.png");
		assert(hBGImageII > 0);
	hBGImageIII = LoadGraph("data/image/Back3.png");
		assert(hBGImageIII > 0);
	// 音声読み込み
	titleBackVoice = LoadSoundMem("data/sound/効果音ラボ/voice/「もうええわ」.mp3");   // 音声 [T]タイトルに戻る
		assert(titleBackVoice > 0);
	changeModeVoice = LoadSoundMem("data/sound/効果音ラボ/voice/「はいは～い♪」.mp3");// 音声 [C]プレイモード変更
		assert(changeModeVoice > 0);

	g = nullptr;
	f = nullptr;

	playTime = 0.0f;		//プレイ時間

	height = 0.0f;			//床文の高さ(10)を引く
	bestHeight = 0.0f;

	changeBGheight = 50 /3;
	gameBGImage = hBGImageI; // デフォルトの背景画像
}

PlayScene::~PlayScene()
{
	DeleteGraph(hBGImageI);			 // 画像 プレイシーン 背景1
	DeleteGraph(hBGImageII);		 // 画像 プレイシーン 背景2
	DeleteGraph(hBGImageIII);		 // 画像 プレイシーン 背景3

	DeleteGraph(playModeTextImage);  // 画像「TETRA」か「BLOCK」
	DeleteGraph(playModeTextImage);  // 画像  プレイエリア プレイモード背景
	DeleteGraph(ladyTextImage);  // 画像「レディ」
	DeleteGraph(goTextImage);  // 画像「ゴー」

	DeleteGraph(nextTextImage);		 // 画像「NEXT」
	DeleteGraph(modeChangeTextImage);// 画像「CHANGE:[C]KEY」

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
		// ボタンを押し込んだ時だけ入力を取る
		if (!isButtonDown) {
			PlaySoundMem(changeModeVoice, DX_PLAYTYPE_BACK);
			//PlayModeクラスから関数を呼び出す
			pm->changeMode();
		}

		isButtonDown = true;
	}
	else {
		isButtonDown = false;
	}

	if (pm->playMode == 0) // テトラモード
	{
		playModeTextImage = LoadGraph("data/image/XA1/xTETRA.png");
			assert(playModeTextImage > 0);
		playModeBGImage = LoadGraph("data/image/TetraSDBig.png");
			assert(playModeBGImage > 0);
	}
	else 				   // ブロックモード
	{
		playModeTextImage = LoadGraph("data/image/XA1/xBLOCK.png");
			assert(playModeTextImage > 0);
		playModeBGImage = LoadGraph("data/image/BlockA1Big.png");
			assert(playModeBGImage > 0);
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
	
	//GOALかFINISHを呼び出し
	if (p->goaled && g == nullptr)
	{
		g = FindGameObject<GoalText>();
		g->resultTime = playTime;
		g->resultHeight = bestHeight;
		// ベストタイム確認 
		CheckBestTime();
		// 確認 
		CheckBestScore();
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
	/*
	// 背景画像表示(本当は連番pngや配列でやりたい)
	DrawGraph(0, -(Screen::HEIGHT * 0) - s->scroll, hBGImageI, TRUE);   //下から１番目
	DrawGraph(0, -(Screen::HEIGHT * 1) - s->scroll, hBGImageII, TRUE);  //下から２番目
	DrawGraph(0, -(Screen::HEIGHT * 2) - s->scroll, hBGImageIII, TRUE); //下から３番目
	*/
	// プレイエリア外のの背景
	DrawGraph(0, 0, gameBGImage, TRUE); // 洞窟の背景

	// プレイモード背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawGraph(30 * 8, 0, playModeBGImage, TRUE); // TETRA/BLOCK
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//「レディ…」→「ゴー！」
	DrawGraph(350, 250, ladyTextImage, TRUE); //「レディ…」
	DrawGraph(430, 230, goTextImage, TRUE);   //「ゴー！」

	//「NEXT」表示
	DrawGraph(1025, 50, nextTextImage, TRUE);

	SetFontSize(25);
	//高さ(playerHeight)
	DrawFormatString(1030, 400, GetColor(255, 255, 255), "HEIGHT:%.0f/50", fabs(height));
	//スコア(Coin?)
	DrawFormatString(1030, 500, GetColor(255, 255, 255), "SCORE:%d", p->gotCoin);
	//タイム(playTime)
	DrawFormatString(1030, 600, GetColor(255, 255, 255), "TIME:%4.2f", playTime);
	
	SetFontSize(20);
	//ベストスコア(bestScore)
	DrawFormatString(1030, 530, GetColor(255, 255, 255), "BEST SCORE:%d", bestTime->GetBestScore() );
	//ベストタイム(bestTime)
	DrawFormatString(1030, 630, GetColor(255, 255, 255), "BEST TIME:%4.2f", bestTime->GetBestTime() );

	//プレイモード(TETRA/BLOCK)
	DrawGraph(5, 530, playModeTextImage, TRUE);  // playModeTextImageに入れる画像を切り替える
	//「CHANGE：[C] KEY」表示
	DrawGraph(5, 600, modeChangeTextImage, TRUE);// modeChangeTextImageに入れる画像を切り替える
}

void PlayScene::CheckBestTime()
{
	// ベストタイムを更新する 
	if (playTime < bestTime->GetBestTime())
	{
		bestTime->SetBestTime(playTime);
	}
}

// ベストスコアを更新
void PlayScene::CheckBestScore()
{
	if (p->gotCoin > bestTime->GetBestScore())
	{
		bestTime->SetBestScore(p->gotCoin);
	}
}

