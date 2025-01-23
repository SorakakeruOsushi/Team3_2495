#pragma once
//GoalText.h
#include "../Library/gameObject.h"
#include "../Library/Utility.h" 

class GoalText :public GameObject
{
public:
	GoalText();
	~GoalText();
	void Update() override;
	void Draw() override;

	XINPUT_STATE input; //PAD操作用変数

	int goalBGImage;		   // 画像 ゴール背景画像
	int finishTextImage;	   // 画像「FINISH!」
	int gameClearTextImage;	   // 画像「GAME CLEAR!」
	int titleBackKeyTextImage; // 画像「スペースキーを押して終了」
	//int thanksTextImage;	   // 画像「Thank You For Playing!」
	int newRecordTextImage;    // 画像「新記録」
	int goalSound;			   // 音 ゲームクリア
	int titleBackSound;		   // 音 タイトルに戻る

	int heightTextImage;	   // 画像「HEIGHT」
	int scoreTextImage;		   // 画像「SCORE」
	int timeTextImage;		   // 画像「TIME」

	float timer; // 表示タイマー
	float alpha; // 不透明度

	float DrawKeyTimer;	 // 表示タイマー「タイトルに戻る」
	bool IsDraw;		 // 描画

	bool IsNewBestScore; // 最高スコア更新
	bool IsNewBestTime;  // 最速タイム更新

	float resultScore;  // スコア結果
	float resultTime; // タイム結果
};
