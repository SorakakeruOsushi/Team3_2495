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
	int finishTextImage;	   // 画像「FINISH!」の文字画像
	int gameClearTextImage;	   // 画像「GAME CLEAR!」の文字画像
	int titleBackKeyTextImage; // 画像「スペースキーを押して終了」の文字画像
	int thanksTextImage;	   // 画像「Thank You For Playing!」の文字画像
	int bannerImage;		   // 画像 バナー
	int goalVoice;			   // 音声 ゲームクリア

	float timer;
	float alpha;
	float bannerSlide;

	float resultTime;
	float resultHeight;
};
