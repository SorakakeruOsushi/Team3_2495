#pragma once
#include "../Library/SceneBase.h"
#include "Stage.h"
#include "GoalText.h"
#include "FinishText.h"
#include "BestTime.h" 

#include "PlayMode.h"


class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;

	XINPUT_STATE input; // PAD操作用変数
	bool isButtonDown;	// プレイモード切り替えで、ボタンの押し込んだ時の入力を取るのに使います

	int nextTextImage;		// 画像「NEXT」の文字画像
	int modeChangeTextImage;// 画像「CHANGE:[C]KEY」の文字画像
	int ladyTextImage; //画像「レディ…」の文字画像
	int goTextImage;   //画像「ゴー！」の文字画像
	int heightTextImage;	//画像「HEIGHT」の文字画像
	int scoreTextImage;		//画像「SCORE」の文字画像
	int timeTextImage;		//画像「TIME」の文字画像
	int bestScoreTextImage;	//画像「BEST SCORE」の文字画像
	int bestTimeTextImage;	//画像「BEST TIME」の文字画像

	int playModeTextImage; // 画像 (現在のプレイモード)の文字画像
	int tetraModeTextImage;// 画像「TETRA」
	int blockModeTextImage;// 画像「BLOCK」
	int playModeBGImage;   // 画像 (現在のプレイモード)プレイエリア背景画像
	int tetraModeBGImage;  // 画像 TETRAモードのプレイエリア背景画像
	int blockModeBGImage;  // 画像 BLOCKモードのプレイエリア背景画像

	int gameBGImage; // 画像 ゲーム背景
	int changeBGheight;
		int hBGImageI;    // 画像 背景1
		int hBGImageII;   // 画像 背景2
		int hBGImageIII;  // 画像 背景3

	int titleBackVoice;		// 音声 [T]タイトルに戻るとき
	int changeModeVoice;	// 音声 [C]プレイモード変更

	float playTime;		//プレイ時間

	float height;	  //高さ
	float bestHeight; //最高の高さ()

	Stage* s;			// マップ
	Player* p;			// プレイヤー
	FinishText* f;		// ゲームオーバー演出表示
	GoalText* g;		// ゴール演出表示
	BestTime* bestTime; // 最速クリアタイム更新
	PlayMode* pm;		// 操作モード切り替え(TETRA/BLOCK)

	void CheckBestTime(); // ベストタイムの更新確認
	void CheckBestScore(); // ベストスコアの更新確認
};