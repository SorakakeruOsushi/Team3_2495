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
	int gameOverVoice;		   // 音声 ゲームオーバー

	float timer; // 表示タイマー
	float alpha; // 不透明度

	float resultTime;	// タイム結果
	float resultHeight; // スコア結果　名前直さなきゃ！
};
