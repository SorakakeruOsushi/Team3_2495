#pragma once
//FinishText.h
#include "../Library/gameObject.h"
#include "../Library/Utility.h" 

class FinishText :public GameObject
{
public:
	FinishText();
	~FinishText();
	void Update() override;
	void Draw() override;

	XINPUT_STATE input; //PAD操作用変数

	int finishTextImage;	   // 画像「FINISH!」
	int gameOverTextImage;	   // 画像「GAME OVER!」
	int titleBackKeyTextImage; // 画像「スペースキーを押して終了」
	int gameOverSound;		   // 音 ゲームオーバー
	int titleBackSound;		   // 音 タイトルに戻る

	int heightTextImage;	// 画像「HEIGHT」
	int scoreTextImage;		// 画像「SCORE」
	int timeTextImage;		// 画像「TIME」

	float timer; // 表示タイマー
	float alpha; // 不透明度

	float DrawKeyTimer;		// 表示タイマー「タイトルに戻る」
	bool IsDraw;			// 描画

	float resultHeight; // 到達高さ
	float resultScore;	// スコア結果 
	float resultTime;	// タイム結果

};
