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

	int finishTextImage;	   // 画像「FINISH!」の文字画像
	int gameOverTextImage;	   // 画像「GAME OVER!」の文字画像
	int titleBackKeyTextImage; // 画像「スペースキーを押して終了」の文字画像
	int bannerImage;		   // 画像 バナー
	int gameOverVoice;		   // 音声 ゲームオーバー

	float timer;
	float alpha;
	float bannerSlide;

	float resultTime;	// タイム結果
	float resultHeight; // スコア結果
};
