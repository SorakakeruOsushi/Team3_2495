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

	int readyGoTextImage; // 
	int readyTextImage;   // 画像「レディ…」
	int goTextImage;      // 画像「ゴー！」

	int stageTextImage;     // 画像 [固定表示文字を１枚の画像にまとめた]
	int resetTextImage;		// 画像「RESET[0]KEY」

	int playModeTextImage;  // 画像 (現在のプレイモード)
	int tetraModeTextImage; // 画像「TETRA」
	int blockModeTextImage; // 画像「BLOCK」
	int playModeBGImage;    // 画像 (現在のプレイモード)プレイエリア背景画像
	int tetraModeBGImage;   // 画像 TETRAモードのプレイエリア背景画像
	int blockModeBGImage;   // 画像 BLOCKモードのプレイエリア背景画像

	int gameBGImage; // 画像 ゲーム背景
	//int changeBGheight;
	//	int hBGImageI;    // 画像 背景1
	//	int hBGImageII;   // 画像 背景2
	//	int hBGImageIII;  // 画像 背景3

	int titleBackSound; // 音 [T]タイトルに戻るとき
	int startSound;		// 音 ゲーム開始
	int resetSound;		// 音 [0]リセット音
	int modeChangeSound;// 音 [C]モード変更時

	float playTime;	  //プレイ時間
	float height;	  // 高さ
	float bestHeight; // 最高の高さ

	float startCountDown;

	Stage* s;			// マップ
	Player* p;			// プレイヤー
	FinishText* f;		// ゲームオーバー演出表示
	GoalText* g;		// ゴール演出表示
	BestTime* bestTime; // 最速クリアタイム更新
	PlayMode* pm;		// 操作モード切り替え(TETRA/BLOCK)

	void CheckBestTime();  // ベストタイムの更新確認
	void CheckBestScore(); // ベストスコアの更新確認
};